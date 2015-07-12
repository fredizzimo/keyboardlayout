#include <iostream>
#include <vector>
#include <string>
#include <array>
#include "optionparser.h"
#include "Optimizer.hpp"
#include "TravelingSalesman.hpp"
#include "mQAP.hpp"


void printError(const char* msg1, const option::Option& opt, const char* msg2)
{
	fprintf(stderr, "ERROR: %s", msg1);
	fwrite(opt.name, opt.namelen, 1, stderr);
	fprintf(stderr, "%s", msg2);
}

option::ArgStatus floatingPoint(const option::Option& option, bool msg)
{
	bool invalid = true;
	try
	{
		if (option.arg)
		{
			std::stof(option.arg);
		}

		invalid = false;
	}
	catch (std::invalid_argument e)
	{
		
	}
	if (!invalid)
	{
		return option::ARG_OK;
	}

	if (msg)
	{
		printError("Option '", option, "' requires a numeric argument\n");
	}
	return option::ARG_ILLEGAL;
}

option::ArgStatus unsignedInteger(const option::Option& option, bool msg)
{
	bool invalid = true;
	try
	{
		if (option.arg)
		{
			std::stoul(option.arg);
		}

		invalid = false;
	}
	catch (std::invalid_argument e)
	{
		
	}
	if (!invalid)
	{
		return option::ARG_OK;
	}

	if (msg)
	{
		printError("Option '", option, "' requires a numeric argument\n");
	}
	return option::ARG_ILLEGAL;
}

option::ArgStatus required(const option::Option& option, bool msg)
{
	if (option.arg)
	{
		return option::ARG_OK;
	}
	else if (msg)
	{
		printError("Option '", option, "' requires a string argument\n");
	}
	return option::ARG_ILLEGAL;
}

enum  optionIndex { UNKNOWN, HELP, MAXT, MINT, NUMSTEPS, TEST, OUTPUT, SEED };
const char* optionNames[] =
{
	"",
	"help",
	"max_t",
	"min_t",
	"steps",
	"test",
	"output",
	"seed"
};

const option::Descriptor usage[] =
{
	{ UNKNOWN, 0, "" , optionNames[UNKNOWN],  option::Arg::None, "USAGE: keyboardlayout [options]\n\nOptions:" },
	{ HELP,    0, "" , optionNames[HELP],     option::Arg::None, "  --help  \tPrint usage and exit." },
	{ MAXT,    0, "" , optionNames[MAXT],     floatingPoint,     "  --max_t  \tThe maximum temperature" },
	{ MINT,    0, "" , optionNames[MINT],     floatingPoint,     "  --min_t  \tThe minimum temperature" },
	{ NUMSTEPS,0, "" , optionNames[NUMSTEPS], floatingPoint,     "  --steps  \tThe number of steps" },
	{ TEST,    0, "" , optionNames[TEST],     required,          "  --test  \tThe name of the test to execute" },
	{ OUTPUT,    0, "" , optionNames[OUTPUT],   required,          "  --output  \tThe name of the output file" },
	{ SEED,    0, "" , optionNames[SEED],     unsignedInteger,   "  --seed  \tThe random seed" },
	{ 0,0,0,0,0,0 }
};

int burma14(float minT, float maxT, int numSteps, unsigned int seed)
{
	std::array<double, 14> latitudes = {
		16.47,
		16.47,
		20.09,
		22.39,
		25.23,
		22.00,
		20.47,
		17.20,
		16.30,
		14.05,
		16.53,
		21.52,
		19.41,
		20.09
	};
	std::array<double, 14> longitudes = {
		96.10,
		94.44,
		92.54,
		93.37,
		97.24,
		96.05,
		97.02,
		96.29,
		97.38,
		98.12,
		97.38,
		95.59,
		97.13,
		94.55
	};
	Optimizer<13> o(seed);
	o.populationSize(1);
	o.numIterations(20);
	o.temperature(maxT, minT, numSteps);
	TravelingSalesman<14> salesman(latitudes, longitudes);
	auto objectives = { salesman };
	auto& solutions = o.optimize(std::begin(objectives), std::end(objectives));
	auto result = solutions.getResult()[0].first;
	int resultValue = static_cast<int>(-std::round(salesman.evaluate(result)));
	return resultValue;
}

int mqap(const std::string filename, float minT, float maxT, int numSteps, unsigned int seed, const std::string outputFile)
{
	mQAP<10> objective1(filename, 0);
	mQAP<10> objective2(filename, 1);
	Optimizer<10> o;
	o.populationSize(50);
	o.numIterations(20);
	o.temperature(maxT, minT, numSteps);
	auto objectives = { objective1, objective2 };
	auto& solutions = o.optimize(std::begin(objectives), std::end(objectives));
	auto result = solutions.getResult();
	std::ofstream f(outputFile, std::ios::out | std::ios::trunc);
	f << "#" << std::endl;
	for (auto&& r: result)
	{
		for (auto&& o : r.second)
		{
			f << o << " ";
		}
		f << std::endl;
	}
	f << "#" << std::endl;
	return 0;
}

int main(int argc, char* argv[])
{
	argc -= (argc > 0); argv += (argc > 0); // skip program name argv[0] if present
	option::Stats stats(usage, argc, argv);

	std::vector<option::Option> options(stats.options_max);
	std::vector<option::Option> buffer(stats.buffer_max);
	option::Parser parse(usage, argc, argv, options.data(), buffer.data());

	if (parse.error())
	{
		option::printUsage(std::cout, usage);
		return 1;
	}

	if (options[HELP] || argc == 0)
	{
		option::printUsage(std::cout, usage);
		return 1;
	}

	for (size_t i = MAXT; i <= NUMSTEPS; ++i)
	{
		if (!options[i])
		{
			std::cout << "Option '" << optionNames[i] << "' is required" << std::endl;
			option::printUsage(std::cout, usage);
			return 1;
		}
	}
	float minT = std::stof(options[MINT].arg);
	float maxT = std::stof(options[MAXT].arg);
	int steps = std::stol(options[NUMSTEPS].arg);
	unsigned int seed = std::stoul(options[SEED].arg);
	if (options[TEST])
	{
		if (strcmp(options[TEST].arg, "burma14") == 0)
		{
			auto res = burma14(minT, maxT, steps, seed);
			std::cout << res << std::endl;
		}
		else
		{
			if (!options[OUTPUT])
			{
				std::cout << "An output file is required" << std::endl;
				return 1;
			}
			auto res = mqap(options[TEST].arg, minT, maxT, steps, seed, options[OUTPUT].arg);
			std::cout << res << std::endl;
		}
	}
}