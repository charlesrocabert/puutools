
/**
 * \file      SEM_run.cpp
 * \author    Charles Rocabert
 * \date      22-09-2020
 * \copyright Copyright © 2020-2021 Charles Rocabert. All rights reserved
 * \license   This project is released under the GNU General Public License
 * \brief     Main executable
 */

/*******************************************************************************
 * Simple Evolvability Model (SEM)
 * Copyright © 2020-2021 Charles Rocabert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/

#include "../cmake/Config.h"

#include <iostream>
#include <string>
#include <cstring>
#include <sys/stat.h>
#include <unordered_map>
#include <fstream>
#include <assert.h>

#include "./lib/Enums.h"
#include "./lib/Structs.h"
#include "./lib/Prng.h"
#include "./lib/Parameters.h"
#include "./lib/Simulation.h"

void readArgs( int argc, char const** argv, Parameters* parameters );
void printUsage( void );
void printHeader( void );


/**
 * \brief    Main function
 * \details  --
 * \param    int argc
 * \param    char const** argv
 * \return   \e int
 */
int main( int argc, char const** argv )
{
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 1) Read command line parameters */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  Parameters* parameters = new Parameters();
  readArgs(argc, argv, parameters);
  parameters->write_parameters();
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 2) Run the simulation           */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  Simulation* simulation = new Simulation(parameters);
  while (simulation->get_generation() <= parameters->get_simulation_time())
  {
    std::cout << ">>> Generation " << simulation->get_generation() << " / " << parameters->get_simulation_time() << "\n";
    simulation->next_generation();
    if (simulation->get_generation() % 500 == 0 && parameters->generate_figures())
    {
      system("Rscript viewer/display_simulation.R > /dev/null &");
    }
  }
  simulation->close_files();
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 3) Free the memory and exit     */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  delete simulation;
  simulation = NULL;
  delete parameters;
  parameters = NULL;
  return EXIT_SUCCESS;
}

/**
 * \brief    Read command line arguments
 * \details  --
 * \param    int argc
 * \param    char const** argv
 * \param    Parameters* parameters
 * \return   \e void
 */
void readArgs( int argc, char const** argv, Parameters* parameters )
{
  std::unordered_map<std::string, bool> options;
  
  /*------------------------------------------------------------------ Main parameters */
  
  options["seed"]                   = false;
  options["nb_dimensions"]          = false;
  options["nb_variable_dimensions"] = false;
  options["burn_in_time"]           = false;
  options["simulation_time"]        = false;
  
  /*------------------------------------------------------------------ Simulation */
  
  options["population_size"]     = false;
  options["mutation_size"]       = false;
  options["point_mutation_rate"] = false;
  options["duplication_rate"]    = false;
  options["deletion_rate"]       = false;
  options["innovation_rate"]     = false;
  options["propagation_steps"]   = false;
  
  /*------------------------------------------------------------------ Environment */
  
  options["alpha"]   = false;
  options["beta"]    = false;
  options["Q"]       = false;
  options["optimum"] = false;
  options["delta"]   = false;
  options["lambda"]  = false;
  
  for (int i = 0; i < argc; i++)
  {
    if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
    {
      printUsage();
      exit(EXIT_SUCCESS);
    }
    if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0)
    {
      std::cout << PACKAGE << " (" << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << ")\n";
      exit(EXIT_SUCCESS);
    }
    
    /*------------------------------------------------------------------ Main parameters */
    
    if (strcmp(argv[i], "-seed") == 0 || strcmp(argv[i], "--seed") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: --seed parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        unsigned long int seed = (unsigned long int)atoi(argv[i+1]);
        if (seed == 0)
        {
          srand((unsigned int)time(NULL));
          seed = rand()%1000000000+1;
        }
        parameters->set_seed(seed);
        options["seed"] = true;
      }
    }
    if (strcmp(argv[i], "-nb_dimensions") == 0 || strcmp(argv[i], "--nb_dimensions") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: --nb_dimensions parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_nb_dimensions(atoi(argv[i+1]));
        options["nb_dimensions"] = true;
      }
    }
    if (strcmp(argv[i], "-nb_variable_dimensions") == 0 || strcmp(argv[i], "--nb_variable_dimensions") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: --nb_variable_dimensions parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_nb_variable_dimensions(atoi(argv[i+1]));
        options["nb_variable_dimensions"] = true;
      }
    }
    if (strcmp(argv[i], "-burn_in_time") == 0 || strcmp(argv[i], "--burn_in_time") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: --burn_in_time parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_burn_in_time(atoi(argv[i+1]));
        options["burn_in_time"] = true;
      }
    }
    if (strcmp(argv[i], "-simulation_time") == 0 || strcmp(argv[i], "--simulation_time") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: --simulation_time parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_simulation_time(atoi(argv[i+1]));
        options["simulation_time"] = true;
      }
    }
    if (strcmp(argv[i], "-generate_figures") == 0 || strcmp(argv[i], "--generate_figures") == 0)
    {
      parameters->set_generate_figures(true);
    }
    if (strcmp(argv[i], "-parallel_computing") == 0 || strcmp(argv[i], "--parallel_computing") == 0)
    {
      parameters->set_parallel_computing(true);
    }
    
    /*------------------------------------------------------------------ Simulation */
    
    if (strcmp(argv[i], "-population_size") == 0 || strcmp(argv[i], "--population_size") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: --population_size parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_population_size(atoi(argv[i+1]));
        options["population_size"] = true;
      }
    }
    if (strcmp(argv[i], "-mutation_size") == 0 || strcmp(argv[i], "--mutation_size") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: --mutation_size parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_mutation_size(atof(argv[i+1]));
        options["mutation_size"] = true;
      }
    }
    if (strcmp(argv[i], "-point_mutation_rate") == 0 || strcmp(argv[i], "--point_mutation_rate") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: --point_mutation_rate parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_point_mutation_rate(atof(argv[i+1]));
        options["point_mutation_rate"] = true;
      }
    }
    if (strcmp(argv[i], "-duplication_rate") == 0 || strcmp(argv[i], "--duplication_rate") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: --duplication_rate parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_duplication_rate(atof(argv[i+1]));
        options["duplication_rate"] = true;
      }
    }
    if (strcmp(argv[i], "-deletion_rate") == 0 || strcmp(argv[i], "--deletion_rate") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: --deletion_rate parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_deletion_rate(atof(argv[i+1]));
        options["deletion_rate"] = true;
      }
    }
    if (strcmp(argv[i], "-innovation_rate") == 0 || strcmp(argv[i], "--innovation_rate") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: --innovation_rate parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_innovation_rate(atof(argv[i+1]));
        options["innovation_rate"] = true;
      }
    }
    if (strcmp(argv[i], "-propagation_steps") == 0 || strcmp(argv[i], "--propagation_steps") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: --propagation_steps parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_propagation_steps(atoi(argv[i+1]));
        options["propagation_steps"] = true;
      }
    }
    
    /*------------------------------------------------------------------ Environment */
    
    if (strcmp(argv[i], "-alpha") == 0 || strcmp(argv[i], "--alpha") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: --alpha parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_alpha(atof(argv[i+1]));
        options["alpha"] = true;
      }
    }
    if (strcmp(argv[i], "-beta") == 0 || strcmp(argv[i], "--beta") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: --beta parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_beta(atof(argv[i+1]));
        options["beta"] = true;
      }
    }
    if (strcmp(argv[i], "-Q") == 0 || strcmp(argv[i], "--Q") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: --Q parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_Q(atof(argv[i+1]));
        options["Q"] = true;
      }
    }
    if (strcmp(argv[i], "-optimum") == 0 || strcmp(argv[i], "--optimum") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: --optimum parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_optimum(atof(argv[i+1]));
        options["optimum"] = true;
      }
    }
    if (strcmp(argv[i], "-delta") == 0 || strcmp(argv[i], "--delta") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: --delta parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_delta(atof(argv[i+1]));
        options["delta"] = true;
      }
    }
    if (strcmp(argv[i], "-lambda") == 0 || strcmp(argv[i], "--lambda") == 0)
    {
      if (i+1 == argc)
      {
        std::cout << "Error: --lambda parameter value is missing.\n";
        exit(EXIT_FAILURE);
      }
      else
      {
        parameters->set_lambda(atof(argv[i+1]));
        options["lambda"] = true;
      }
    }
  }
  bool parameter_lacking = false;
  for (auto it = options.begin(); it != options.end(); ++it)
  {
    if (!it->second)
    {
      std::cout << "-" << it->first << " option is mandatory.\n";
      parameter_lacking = true;
    }
  }
  if (parameter_lacking)
  {
    exit(EXIT_FAILURE);
  }
}

/**
 * \brief    Print usage
 * \details  --
 * \param    void
 * \return   \e void
 */
void printUsage( void )
{
  std::cout << "\n";
  std::cout << "*********************************************************************\n";
#ifdef DEBUG
  std::cout << " " << PACKAGE << " " << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << " ( debug )\n";
#endif
#ifdef NDEBUG
  std::cout << " " << PACKAGE << " " << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << " ( release )\n";
#endif
  std::cout << " Copyright © 2020-2021 Charles Rocabert                              \n";
  std::cout << "                                                                     \n";
  std::cout << " This program comes with ABSOLUTELY NO WARRANTY.                     \n";
  std::cout << " This is free software, and you are welcome to redistribute it under \n";
  std::cout << " certain conditions; See the GNU General Public License for details  \n";
  std::cout << "*********************************************************************\n";
  std::cout << "\n";
  std::cout << "Run a simulation:\n";
  std::cout << "-----------------\n";
  std::cout << "Usage: SEM_run -h or --help\n";
  std::cout << "   or: SEM_run [options]\n";
  std::cout << "Options are:\n";
  std::cout << "  -h, --help\n";
  std::cout << "        print this help, then exit (optional)\n";
  std::cout << "  -v, --version\n";
  std::cout << "        print the current version, then exit (optional)\n";
  std::cout << "  -seed, --seed\n";
  std::cout << "        specify the seed of the pseudorandom numbers generator\n";
  std::cout << "  -population_size, --population_size\n";
  std::cout << "        specify the population size\n";
  std::cout << "  -nb_dimensions, --nb_dimensions\n";
  std::cout << "        specify the number of dimensions of the phenotypic space\n";
  std::cout << "  -nb_variable_dimensions, -nb_variable_dimensions\n";
  std::cout << "        specify the number of variable dimensions\n";
  std::cout << "  -burn_in_time, --burn_in_time\n";
  std::cout << "        specify the burn-in time (in generations)\n";
  std::cout << "  -simulation_time, --simulation_time\n";
  std::cout << "        specify the simulation time (in generations)\n";
  std::cout << "  -mutation_size, --mutation_size\n";
  std::cout << "        specify the mutation size\n";
  std::cout << "  -point_mutation_rate, --point_mutation_rate\n";
  std::cout << "        specify the point mutation rate\n";
  std::cout << "  -duplication_rate, --duplication_rate\n";
  std::cout << "        specify the duplication rate\n";
  std::cout << "  -deletion_rate, --deletion_rate\n";
  std::cout << "        specify the deletion rate\n";
  std::cout << "  -innovation_rate, --innovation_rate\n";
  std::cout << "        specify the innovation rate\n";
  std::cout << "  -propagation_steps, --propagation_steps\n";
  std::cout << "        specify the number of GRN propagation steps\n";
  std::cout << "  -alpha, --alpha\n";
  std::cout << "        beta fitness landscape's alpha parameter\n";
  std::cout << "  -beta, --alpha\n";
  std::cout << "        specify fitness landscape's beta parameter\n";
  std::cout << "  -Q, --Q\n";
  std::cout << "        specify fitness landscape's Q parameter\n";
  std::cout << "  -optimum, --optimum\n";
  std::cout << "        specify environmental default optimum parameter\n";
  std::cout << "  -delta, --delta\n";
  std::cout << "        specify environmental change amount parameter\n";
  std::cout << "  -lambda, --lambda\n";
  std::cout << "        specify environmental change lambda parameter\n";
  std::cout << "  -generate_figures, --generate_figures\n";
  std::cout << "        indicates if figures should be generated (optional)\n";
  std::cout << "  -parallel_computing, --parallel_computing\n";
  std::cout << "        indicates if the computing should be parallel (optional)\n";
  std::cout << "\n";
}

/**
 * \brief    Print header
 * \details  --
 * \param    void
 * \return   \e void
 */
void printHeader( void )
{
  std::cout << "\n";
  std::cout << "*********************************************************************\n";
#ifdef DEBUG
  std::cout << " " << PACKAGE << " " << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << " ( debug )\n";
#endif
#ifdef NDEBUG
  std::cout << " " << PACKAGE << " " << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << " ( release )\n";
#endif
  std::cout << " Copyright © 2020-2021 Charles Rocabert                              \n";
  std::cout << "                                                                     \n";
  std::cout << " This program comes with ABSOLUTELY NO WARRANTY.                     \n";
  std::cout << " This is free software, and you are welcome to redistribute it under \n";
  std::cout << " certain conditions; See the GNU General Public License for details  \n";
  std::cout << "*********************************************************************\n";
  std::cout << "Run a simulation.\n";
  std::cout << "\n";
}



