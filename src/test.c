#include "example-clientlet.c"
#include "stdio.h"

void print_with_code(const char* name, int code, const char* result){
    if(code >= 0){
        printf("Successfully executed task '%s' with code 0 and result '%s'\n", name, result);
    } else {
        printf("Executing task '%s' resulted in errors with code %d\n", name, code);
    }
}


void print_elements(json_element* root){

    if(root->type == JSON_ELEMENT_STRING){
        printf("'%s':'%s'", string_view_to_c_string(&root->name), string_view_to_c_string(root->content));
    } else if (root->type == JSON_ELEMENT_OBJECT) {
        printf("'%s':{", string_view_to_c_string(&root->name));
        json_element* elem = root->content;
        while(elem != (void*)0){
            print_elements(elem);
            elem = elem->next;
        }
        printf("}");
    } else if(root->type == JSON_ELEMENT_ARRAY_EMPTY){
        printf("'%s':[]", string_view_to_c_string(&root->name));
    } else if (root->type == JSON_ELEMENT_ARRAY_OF_STRINGS || root->type == JSON_ELEMENT_ARRAY_OF_OBJECTS) {
        printf("'%s': [", string_view_to_c_string(&root->name));
        json_element* elem = root->content;
        while(elem != (void*)0){
            print_elements(elem);
            elem = elem->next;
        }
        printf("]");
    }

}

void test_read_string_til_next_quotation() {
    const char* source1 = "This is String ending with a quotation\"";
    string_view string1;
    int code1 = json_parse_string_til_next_quotation_mark(source1, 0, &string1);
    print_with_code("Parsing string with quotation at the end", code1, string_view_to_c_string(&string1));
}

void test_skip_til_char() {
    const char* source = "                    h"; //h bei 21
    int res = json_skip_til_char_only_skippables(source, 0, 'h');
    printf("Skippable test: Erwartet wird h an Stelle 21. Erhalten: h an Stelle %d. Test bestanden: %d\n", res, res == 21);
}

void test_skip_til_next_unskippable_char(){
    const char* source = "\n      \t      \t  a:b  ";
    int pos = json_jump_to_next_unskippable_char(source, 0);
    printf("Jump to next unskippable character: Expected (:), Received (%c) at pos %d\n", source[pos], pos);
}

void test_char_in_charset(){
    char skippable = ' ';
    char unskippable = ':';
    bool _skippable = char_in_char_set(skippable, JSON_SYNTAX_ALLOWED_SKIPPABLES);
    bool _unskippable = char_in_char_set(unskippable, JSON_SYNTAX_ALLOWED_SKIPPABLES);
    printf("Char in char set test: '%c' is skippable (%i) and '%c' is not skippale (%i)\n", skippable, _skippable,
                                                                                            unskippable, _unskippable);
}

void test_first_object() {
    const char* source = "\n{ \n\t\"name\"  :  \"Daniel Mehlber\", \"age\":\"18\", \"freunde\":[\"Sandra\", \"Matthias\"]}\n";
    json_parser_result result = json_parse_source(source, "person");
    if(!result.success){
        printf("Object parsing failed with code %i", result.code);
    }
    print_elements(result.root);
}

void test_string_builder() {
    char* _0 = "Hallo ich ";
    char* _1 = "bin der ";
    char* _2 = "Daniel";

    string_builder* builder = new_string_builder();
    string_builder_add_string(builder, _0);
    string_builder_add_string(builder, _1);
    string_builder_add_string(builder, _2);

    const char* text = string_builder_to_c_string(builder);

    printf("%s", text);
}



int main(){
    //test_read_string_til_next_quotation();
    //test_skip_til_char();
    //test_char_in_charset();
    //test_skip_til_next_unskippable_char();
    //test_first_object();
    //test_string_builder();
    printf("%s", build());
}
