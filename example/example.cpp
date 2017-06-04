#include "../include/crap.hpp"

int main(int argc, char * argv[])
{
	crap::KeyArg programArg(argv[0]);
	programArg.setRequired(true);

	crap::Parser parser(& programArg);
	parser.setOptionRequired(true);
	parser.setHeader("C++RAP Example\n\n");
	parser.setFooter("\n(c)700BCE Ra Inc.\n");

	crap::KeyArg verboseArg("--verbose", "Print verbose messages.");
	verboseArg.addAlias("-v");
	parser.addAttr(& verboseArg);

	crap::ArgGroup pyramidArgsGroup("pyramid_options");
	crap::KeyValueArg pNameArg("pname", "name", "Pyramid name.");
	pNameArg.setDefaultValue("Cheops");
	pyramidArgsGroup.addAttr(& pNameArg);
	crap::KeyValueArg pStonesArg("pstones", "number", "Specifies <number> of stones used to build a pyramid.");
	pStonesArg.setRequired(true);
	pyramidArgsGroup.addAttr(& pStonesArg);

	crap::KeyArg initArg("init", "Initialize pyramid construction site.");
	parser.addSubCmd(& initArg)->addArgGroup(& pyramidArgsGroup);

	crap::KeyValueArg employArg("employ", "amount", "Employ <amount> of slaves.");
	employArg.setDefaultValue("1000");
	parser.addSubCmd(& employArg);

	crap::ArgGroup renameArgsGroup("rename_options");
	crap::ValueArg oldPyramidArg("old_name", "Old pyramid name.");
	oldPyramidArg.setRequired(true);
	renameArgsGroup.addAttr(& oldPyramidArg);
	crap::ValueArg newPyramidArg("new_name", "New pyramid name.");
	newPyramidArg.setRequired(true);
	renameArgsGroup.addAttr(& newPyramidArg);

	crap::KeyArg renameArg("rename", "Rename pyramid");
	parser.addSubCmd(& renameArg)->addArgGroup(& renameArgsGroup);

	crap::KeyArg buildArg("build", "Build a pyramid.");
	parser.addSubCmd(& buildArg);

	crap::KeyArg helpArg("help", "Print this information.");
	helpArg.addAlias("--help").addAlias("-h");
	parser.addSubCmd(& helpArg);

	try {
		parser.parse(argc, argv);
	} catch (const crap::Exception & e) {
		std::cout << "\n" << e.what() << "\n\n";
		parser.printSynopsis();
		std::cout << "\n";
		return EXIT_FAILURE;
	}

	if (initArg.isSet()) {
		std::cout << "Initializing pyramid construction site.\n";
		std::cout << "Pyramid name: " << pNameArg.value() << "\n";
		std::cout << "Amount of stones: " << pStonesArg.value() << "\n";
	} else if (employArg.isSet())
		std::cout << "Employing " << employArg.value() << " slaves.\n";
	else if (renameArg.isSet()) {
		std::cout << "Renaming pyramid " << oldPyramidArg.value() << " to " << newPyramidArg.value() << ".\n";
	} else if (buildArg.isSet())
		std::cout << "Building a pyramid.\n";
	else if (helpArg.isSet())
		parser.printHelp(std::cout);

	if (verboseArg.isSet())
		std::cout << "Verbose information...\n";

	return EXIT_SUCCESS;
}
