/* SQLite Architecture

    _core_ "FrontEnd"
         _Interface
         _SQLCommandProcessor :: _SQLCompiler_
         _Virtual Machine :: _BackEnd_
    
    _SQLCompiler_
         _Tokenizer
         _Parser
         _CodeGenerator -> SQLCommandProcessor
    _BackEnd_
         _BTree
         _Pager
         _OSInterface

    _Accessoiries_
         _Utilities
         _Test Code
*/

#include "API.h"
// SQLite REPL : read-execute-print-loop
int main(int argc, char* argv[]) {
    Table* table = new_table();
    InputBuffer* input_buffer = new_input_buffer();
    while (true) {
        print_prompt();
        read_input(input_buffer);
            
        if (input_buffer->buffer[0] == '.') {
            switch (do_meta_command(input_buffer, table)) {
                case (META_COMMAND_SUCCESS):
                    continue;
                case (META_COMMAND_UNRECOGNIZED_COMMAND):
                    printf("Unrecognized command '%s'.\n", input_buffer->buffer);
                    continue;
            }
        }

        Statement statement;
        switch (prepare_statment(input_buffer, &statement)) {
            case (PREPARE_SUCCESS):
                break;
            case (PREPARE_SYNTAX_ERROR):
                printf("Synatx error. Could not parse statement.\n");
                continue;
            case (PREPARE_UNRECOGNIZED_STATEMENT):
                printf("Unrecognized keyword at start of '%s'.\n", input_buffer->buffer);
                continue;
        }

        switch (execute_statement(&statement, table)) {
            case (EXECUTE_SUCCESS):
                printf("Executed.\n");
                break;
            case (EXECUTE_TABLE_FAIL):
                printf("Error: Table full.\n");
                break;
        }
        
    }
}