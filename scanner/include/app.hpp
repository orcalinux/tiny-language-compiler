/**
 * @file app.hpp
 *
 * @brief This file defines the App class, which manages the execution of the application.
 *
 * The App class is responsible for parsing command-line arguments, validating input,
 * and running the application in either interactive mode or file mode.
 */
#ifndef APP_HPP
#define APP_HPP

#include <getopt.h>

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "file_handler.hpp"
#include "scanner.hpp"
#include "token.hpp"
#include "token_stream_builder.hpp"

/**
 * @class App
 * @brief Manages the execution of the application.
 *
 * The App class is responsible for parsing command-line arguments, validating input,
 * and running the application in either interactive mode or file mode.
 *
 * @note The constructor initializes the App object but does not run the application.
 *       To run the application, call the run() method.
 */
class App {
   public:
    /**
     * @brief Constructs an App object, parses command-line arguments, and validates input.
     *
     * This constructor initializes the App object by parsing the command-line arguments
     * provided. It checks if the input file path is specified, if the application is in
     * interactive mode, or if help is requested. If none of these conditions are met,
     * it throws an invalid_argument exception.
     *
     * @param argc The number of command-line arguments.
     * @param argv The array of command-line arguments.
     *
     * @throws std::invalid_argument If the input file is not specified and the application
     *         is not in interactive mode or help mode.
     *
     * @note The constructor doesn't run the application. To run the application, call the run() method.
     */
    App(int argc, char *argv[]);

    /**
     * @brief Executes the application based on the current mode.
     *
     * This function checks the state of the application and runs it in either
     * interactive mode or file mode. If the help flag is set, it does not run
     * any mode.
     *
     * - If `showHelp` is true, the function does nothing.
     * - If `interactiveMode` is true, it runs the application in interactive mode.
     * - Otherwise, it runs the application in file mode.
     */
    void run();

   private:
    bool showHelp = false;                /**< Flag to show help message */
    bool showOutput = false;              /**< Flag to show output in the console */
    bool includeTokenPosition = false;    /**< Flag to include token position in output */
    std::string inputFilePath;            /**< Path to the input file */
    std::string outputFilePath;           /**< Path to the output file */
    bool interactiveMode = false;         /**< Flag to run the application in interactive mode */
    std::string terminateKeyword = "END"; /**< Keyword to terminate interactive mode */
    bool hasOutputFile = false;           /**< Flag to indicate if an output file is specified */

    /**
     * @brief Runs the application in interactive mode.
     *
     * This function continuously reads TINY code input from the user until the
     * terminate keyword is entered. It then initializes the scanner and token
     * stream builder, builds the token stream, and optionally prints the tokens
     * to the console and writes them to an output file.
     *
     * The function performs the following steps:
     * 1. Reads input from the user until the terminate keyword is entered.
     * 2. Initializes the scanner with the input content.
     * 3. Initializes the token stream builder with the scanner.
     * 4. Builds the token stream.
     * 5. If showOutput is true, prints the tokens to the console.
     * 6. If hasOutputFile is false, writes the tokens to the specified output file.
     */
    void runInteractiveMode();

    /**
     * @brief Runs the application in file mode.
     *
     * This function reads the input file, initializes the scanner and token stream builder,
     * builds the token stream, and optionally prints the tokens to the console and writes
     * them to an output file.
     *
     * @details
     * - Reads the content of the input file specified by `inputFilePath`.
     * - Initializes the `Scanner` with the input file content.
     * - Initializes the `TokenStreamBuilder` with the scanner.
     * - Builds the token stream using the `TokenStreamBuilder`.
     * - If `showOutput` is true, prints the tokens to the console.
     * - If `hasOutputFile` is false, writes the tokens to the output file specified by `outputFilePath`.
     *
     */
    void runFileMode();

    /**
     * @brief Prints the list of tokens to the standard output.
     *
     * This function iterates through the provided vector of tokens and prints
     * each token's string representation. If the includePosition flag is set to true,
     * the position information of each token will also be included in the output.
     *
     * @param tokens A vector containing the tokens to be printed.
     * @param includePosition A boolean flag indicating whether to include position
     *                        information in the token's string representation.
     */
    void printTokens(const std::vector<Token> &tokens, bool includePosition = false);

    /**
     * @brief Processes the tokens from the input file content.
     *
     * This function initializes the scanner and token stream builder, builds the token stream,
     * and optionally prints the tokens to the console or writes them to an output file.
     *
     * @param inputFileContent The content of the input file to be processed.
     * @throws std::invalid_argument If the input file content is empty.
     *
     * TODO: Uncomment the following code after implementing the Scanner and TokenStreamBuilder classes
     */
    void processTokens(std::string &inputFileContent);

    /**
     * @brief Prints the help message for the scanner application.
     *
     * This function outputs the usage instructions and available options for the
     * scanner application. It provides details on how to specify input and output
     * files, choose the mode of operation, and other optional parameters.
     *
     * @see parseArgs
     */
    void printHelp();

    /**
     * @brief Parses command-line arguments and sets the corresponding application parameters.
     *
     * This function processes both short and long command-line options to configure the application.
     * The supported options are:
     *
     * -h, --help
     *     Display help information and exit.
     *
     * -i, --input <file>
     *     Specify the input file path.
     *
     * -o, --output <file>
     *     Specify the output file path.
     *
     * -m, --mode <mode>
     *     Set the mode of operation. Valid values are 'interactive' and 'file'.
     *
     * -s, --show-output
     *     Enable the display of output.
     *
     * --include-token-position
     *     Include token position information in the output.
     *
     * --default-output
     *     Use the default output file path ("output.txt").
     *
     * -t, --terminate-keyword <keyword>
     *     Specify a keyword that will terminate the processing.
     *
     * @param argc The number of command-line arguments.
     * @param argv The array of command-line arguments.
     *
     * @throws std::invalid_argument If an invalid mode is specified.
     *
     * @see getopt_long
     */
    void parseArgs(int argc, char *argv[]);

    /**
     * @brief Handles positional arguments passed to the application.
     *
     * This function processes the positional arguments provided via the command line.
     * It stores the arguments in a vector and assigns the first positional argument
     * to the input file path. If a second positional argument is provided, it assigns
     * it to the output file path. If no output file path is specified, it defaults to "output.txt".
     *
     * @param argc The number of command-line arguments.
     * @param argv The array of command-line arguments.
     */
    void handlePositionalArgs(int argc, char *argv[]);
};

#endif  // APP_HPP