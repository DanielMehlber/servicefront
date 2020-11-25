//#include "include/emscripten.h"
#include "json.h"

const char* _0 = "<html><head></head><body>";
const char* _1 = ", ";
const char* _2 = "</body></html>";

const char* json_0 = "{\"name\":\"Daniel Mehlber\", \"age\":\"18\"}";
const char* json_0_name = "person";


const char* get_element_string(json_element* elem){
    if(elem == (void*)0) return "<not-found>";
    return elem->content != (void*)0 ? string_view_to_c_string(elem->content) : "<value-error>";
}

//EMSCRIPTEN_KEEPALIVE
const char* build(){
    json_parser_result person_result = json_parse_source(json_0, json_0_name);
    if(!person_result.success){
        return "AN ERROR WHILE EXECUTING ECCURED IN JSON PARSER";
    }
    json_element* _person = person_result.root;

    string_builder* builder = new_string_builder();
    string_builder_add_string(builder, _0);

    const char* _person_name = get_element_string(json_element_object_get_child_with_name(_person, "name"));
    string_builder_add_string(builder, _person_name);
    
    string_builder_add_string(builder, _1);

    const char* _person_age = get_element_string(json_element_object_get_child_with_name(_person, "age"));
    string_builder_add_string(builder, _person_age);

    string_builder_add_string(builder, _2);

    return string_builder_to_c_string(builder);
}