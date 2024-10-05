import os
import sys,getopt
import xml.etree.ElementTree as xml_et
import copy

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

class _element:
    _name = ""
    _id = ""
    _description = ""

class _enum:
    _name = ""
    _element = []

class _message:
    _name = ""
    _description = ""

class _message_type_enum:
    _name = ""
    _type = ""
    _description = ""

_list_message_int8 = []
_list_message_int16 = []
_list_message_int32 = []
_list_message_int64 = []
_list_message_uint8 = []
_list_message_uint16 = []
_list_message_uint32 = []
_list_message_uint64 = []
_list_message_bool = []
_list_message_float = []
_list_message_double = []
_list_message_string = []
_list_message_enum = []
_list_enum = []






def _deal_enum(c_enum : xml_et.Element) -> int:

    if "name" in c_enum.attrib:
        enum_name = c_enum.attrib["name"]
    else:
        print(bcolors.FAIL + "ERROR: NONE ENUM NAME" + bcolors.ENDC)
        return -1
    
    t_enum = _enum()
    # t_enum._element.clear()
    t_enum._name = enum_name
    
    for enum_element in c_enum.findall("element"):
        if "name" in enum_element.attrib:
            element_name = enum_element.attrib["name"]
        else:
            print(bcolors.FAIL + "ERROR: NONE ELEMENT NAME" + bcolors.ENDC)  
            return -1
        
        if "id" in enum_element.attrib:
            element_id = enum_element.attrib["id"]
        else:
            element_id = ""
        element_description = enum_element.text

        t_element = _element()
        t_element._name = element_name
        t_element._id = element_id
        t_element._description = element_description
        t_enum._element.append(t_element)
        # print(len(t_enum._element))

    # 判断enum是否重名
    for message_enum in _list_enum:
        if(enum_name == message_enum._name):
            print(bcolors.FAIL + "ERROR: ENUM NAME WAS REPEAT" + bcolors.ENDC)
            return -1
    
    # ??????????? 为了列表数据不改变
    new_enum = copy.deepcopy(t_enum)
    new_enum._element = copy.deepcopy(t_enum._element)
    _list_enum.append(copy.deepcopy(new_enum))
    t_enum._element.clear()
    return 0







def _deal_message(m_message : xml_et.Element) -> int:
    if "name" in m_message.attrib:
        message_name = m_message.attrib["name"]
    else:
        print(bcolors.FAIL + "ERROR: NONE MESSAGE NAME" + bcolors.ENDC)
        return -1
    
    if "type" in m_message.attrib:
        message_type = m_message.attrib["type"]
    else:
        print(bcolors.FAIL + "ERROR: NONE MESSAGE TYPE" + bcolors.ENDC)
        return -1
    
    message_description = m_message.text
    t_message = _message()
    t_message._name = message_name
    t_message._description = message_description
    
    # match --case  ?
    if message_type == "int8":
        _list_message_int8.append(t_message)
    elif message_type == "int16":
        _list_message_int16.append(t_message)
    elif message_type == "int32":
        _list_message_int32.append(t_message)
    elif message_type == "int64":
        _list_message_int64.append(t_message)
    elif message_type == "uint8":
        _list_message_uint8.append(t_message)
    elif message_type == "uint16":
        _list_message_uint16.append(t_message)
    elif message_type == "uint32":
        _list_message_uint32.append(t_message)
    elif message_type == "uint64":
        _list_message_uint64.append(t_message)
    elif message_type == "bool":
        _list_message_bool.append(t_message)
    elif message_type == "float":
        _list_message_float.append(t_message)
    elif message_type == "double":
        _list_message_double.append(t_message)
    elif message_type == "string":
        _list_message_string.append(t_message)
    else :
        for have_enum in _list_enum:
            is_have = False
            if message_type == have_enum._name:
                t_message_type_enum = _message_type_enum()
                t_message_type_enum._name = message_name
                t_message_type_enum._description = message_description
                t_message_type_enum._type = message_type
                _list_message_enum.append(t_message_type_enum)
                is_have = True
                break
        if False == is_have :
            print(bcolors.FAIL + "ERROR: NOT FIND THIS ENUM: " + message_type + bcolors.ENDC)
            return -1
    return 0






def _clear_list():
    _list_message_int8.clear()
    _list_message_int16.clear()
    _list_message_int32.clear()
    _list_message_int64.clear()
    _list_message_uint8.clear()
    _list_message_uint16.clear()
    _list_message_uint32.clear()
    _list_message_uint64.clear()
    _list_message_bool.clear()
    _list_message_float.clear()
    _list_message_double.clear()
    _list_message_string.clear()
    _list_message_enum.clear()
    _list_enum.clear()







def _deal_cpp_class(c_class : xml_et.Element, file_h, file_cc) -> int:
    if "name" in c_class.attrib:
        class_name = c_class.attrib["name"]
    else:
        print(bcolors.FAIL + "ERROR: NONE CLASS NAME" + bcolors.ENDC)
        return -1
    
    for c_enum in c_class.findall("enum"):
        if -1 == _deal_enum(c_enum):
            _clear_list()
            return -1
        
    for c_message in c_class.findall("message"):
        if -1 == _deal_message(c_message):
            _clear_list()
            return -1
        
    # print(_list_message_int8)
    if -1 == _generate_potatobuf_cpp( file_h, file_cc, class_name) :
        _clear_list()
        return -1
    
    _clear_list()
    return 0

# 
is_frist = True

def _generate_potatobuf_init_message(file_h, list_message:list):
    global is_frist
    for message in list_message :
        if is_frist :
            file_h.write(" :\n\t\t" + message._name + "(0)")
            is_frist = False
        else :
            file_h.write(",\n\t\t" + message._name + "(0)")

_namespace = ""

# 生成 h，cc 中 class 内容
def _generate_potatobuf_cpp( file_h, file_cc , class_name : str) -> int:
    
    # .h
    file_h.write("class " + class_name + " final : public PotatoBuffer::_potatobuf\n{\n")
    file_h.write("public:\n")
    file_h.write("\t" + class_name + "()")

    _generate_potatobuf_init_message(file_h, _list_message_int8)
    _generate_potatobuf_init_message(file_h, _list_message_int16)
    _generate_potatobuf_init_message(file_h, _list_message_int32)
    _generate_potatobuf_init_message(file_h, _list_message_int64)
    _generate_potatobuf_init_message(file_h, _list_message_uint8)
    _generate_potatobuf_init_message(file_h, _list_message_uint16)
    _generate_potatobuf_init_message(file_h, _list_message_uint32)
    _generate_potatobuf_init_message(file_h, _list_message_uint64)

    global is_frist
    for message_bool in _list_message_bool :
        if is_frist :
            file_h.write(" :\n\t\t" + message_bool._name + "(false)")
            is_frist = False
        else :
            file_h.write(",\n\t\t" + message_bool._name + "(false)")
    for message_float in _list_message_float :
        if is_frist :
            file_h.write(" :\n\t\t" + message_float._name + "(0.0f)")
            is_frist = False
        else :
            file_h.write(",\n\t\t" + message_float._name + "(0.0f)")
    for message_double in _list_message_double :
        if is_frist :
            file_h.write(" :\n\t\t" + message_double._name + "(0.0)")
            is_frist = False
        else :
            file_h.write(",\n\t\t" + message_double._name + "(0.0)")

    for message_enum in _list_message_enum :
        if is_frist :
            file_h.write(" :\n\t\t" + message_enum._name + "(" + message_enum._type + "(0))")
            is_frist = False
        else :
            file_h.write(",\n\t\t" + message_enum._name + "(" + message_enum._type + "(0))")
    is_frist = True

    file_h.write("\n\t{\n\t\tINIT_MSG_NUM(" + str(len(_list_message_int8)) + "," \
                                            + str(len(_list_message_int16)) + "," \
                                            + str(len(_list_message_int32)) + "," \
                                            + str(len(_list_message_int64)) + "," \
                                            + str(len(_list_message_uint8)) + "," \
                                            + str(len(_list_message_uint16)) + "," \
                                            + str(len(_list_message_uint32)) + "," \
                                            + str(len(_list_message_uint64)) + "," \
                                            + str(len(_list_message_bool)) + "," \
                                            + str(len(_list_message_float)) + "," \
                                            + str(len(_list_message_double)) + "," \
                                            + str(len(_list_message_enum)) + "," \
                                            + str(len(_list_message_string)) + ");\n\t}\n\n")
    
    file_h.write("\t~" + class_name + "(){}\n\n")
    file_h.write("\tsize_t SerializeToString(std::string& str) override;\n")
    file_h.write("\tchar* SerializeToCString(size_t& len) override;\n")
    file_h.write("\tint SerializeFromString(std::string& str) override;\n")
    file_h.write("\tint SerializeFromCString(char* c_str, size_t len) override;\n")

    for t_enum in _list_enum:
        file_h.write("\n\t//" + t_enum._name + "\n")
        file_h.write("\tenum class " + t_enum._name + " : int {\n")
        # print(len(t_enum._element))
        for t_element in t_enum._element :
            id = t_element._id
            if not "" == id :
                id = " = " + id
            if is_frist :
                file_h.write("\t\t" + t_element._name + id)
                is_frist = False
            else :
                file_h.write(",\n\t\t" + t_element._name + id)
        file_h.write("\n\t};\n\n")
        is_frist = True

    for msg_int8 in _list_message_int8:
        file_h.write("\t//" + msg_int8._name +"\n\t//" + str(msg_int8._description) + "\n")
        file_h.write("\tADD_MSG(P_INT8 ," + msg_int8._name +")\n\n")
    for msg_int16 in _list_message_int16:
        file_h.write("\t//" + msg_int16._name +"\n\t//" + str(msg_int16._description) + "\n")
        file_h.write("\tADD_MSG(P_INT16 ," + msg_int16._name +")\n\n")
    for msg_int32 in _list_message_int32:
        file_h.write("\t//" + msg_int32._name +"\n\t//" + str(msg_int32._description) + "\n")
        file_h.write("\tADD_MSG(P_INT32 ," + msg_int32._name +")\n\n")
    for msg_int64 in _list_message_int64:
        file_h.write("\t//" + msg_int64._name +"\n\t//" + str(msg_int64._description) + "\n")
        file_h.write("\tADD_MSG(P_INT64 ," + msg_int64._name +")\n\n")
    for msg_uint8 in _list_message_uint8:
        file_h.write("\t//" + msg_uint8._name +"\n\t//" + str(msg_uint8._description) + "\n")
        file_h.write("\tADD_MSG(P_UINT8 ," + msg_uint8._name +")\n\n")
    for msg_uint16 in _list_message_uint16:
        file_h.write("\t//" + msg_uint16._name +"\n\t//" + str(msg_uint16._description) + "\n")
        file_h.write("\tADD_MSG(P_UINT16 ," + msg_uint16._name +")\n\n")
    for msg_uint32 in _list_message_uint32:
        file_h.write("\t//" + msg_uint32._name +"\n\t//" + str(msg_uint32._description) + "\n")
        file_h.write("\tADD_MSG(P_UINT32 ," + msg_uint32._name +")\n\n")
    for msg_uint64 in _list_message_uint64:
        file_h.write("\t//" + msg_uint64._name +"\n\t//" + str(msg_uint64._description) + "\n")
        file_h.write("\tADD_MSG(P_UINT64 ," + msg_uint64._name +")\n\n")
    for msg_bool in _list_message_bool:
        file_h.write("\t//" + msg_bool._name +"\n\t//" + str(msg_bool._description) + "\n")
        file_h.write("\tADD_MSG(bool ," + msg_bool._name +")\n\n")
    for msg_float in _list_message_float:
        file_h.write("\t//" + msg_float._name +"\n\t//" + str(msg_float._description) + "\n")
        file_h.write("\tADD_MSG(float ," + msg_float._name +")\n\n")
    for msg_double in _list_message_double:
        file_h.write("\t//" + msg_double._name +"\n\t//" + str(msg_double._description) + "\n")
        file_h.write("\tADD_MSG(double ," + msg_double._name +")\n\n")
    for msg_enum in _list_message_enum:
        file_h.write("\t//" + msg_enum._name +"\n\t//" + str(msg_enum._description) + "\n")
        file_h.write("\tADD_MSG_ENUM(" + msg_enum._type + ", " + msg_enum._name +")\n\n")
    for msg_string in _list_message_string:
        file_h.write("\t//" + msg_string._name +"\n\t//" + str(msg_string._description) + "\n")
        file_h.write("\tADD_MSG_STRING(" + msg_string._name +")\n\n")

    file_h.write("private:\n")
    for msg_int8 in _list_message_int8:
        file_h.write("\tP_INT8 " + msg_int8._name +";\n")
    for msg_int16 in _list_message_int16:
        file_h.write("\tP_INT16 " + msg_int16._name +";\n")
    for msg_int32 in _list_message_int32:
        file_h.write("\tP_INT32 " + msg_int32._name +";\n")
    for msg_int64 in _list_message_int64:
        file_h.write("\tP_INT64 " + msg_int64._name +";\n")
    for msg_uint8 in _list_message_uint8:
        file_h.write("\tP_UINT8 " + msg_uint8._name +";\n")
    for msg_uint16 in _list_message_uint16:
        file_h.write("\tP_UINT16 " + msg_uint16._name +";\n")
    for msg_uint32 in _list_message_uint32:
        file_h.write("\tP_UINT32 " + msg_uint32._name +";\n")
    for msg_uint64 in _list_message_uint64:
        file_h.write("\tP_UINT64 " + msg_uint64._name +";\n")
    for msg_bool in _list_message_bool:
        file_h.write("\tbool " + msg_bool._name +";\n")
    for msg_float in _list_message_float:
        file_h.write("\tfloat " + msg_float._name +";\n")
    for msg_double in _list_message_double:
        file_h.write("\tdouble " + msg_double._name +";\n")
    for msg_enum in _list_message_enum:
        file_h.write("\t" + msg_enum._type + " " + msg_enum._name +";\n")
    for msg_string in _list_message_string:
        file_h.write("\tstd::string " + msg_string._name +";\n")

    file_h.write("}; // class " + class_name + "\n\n")

    # .cc
    global _namespace
    if not "" == _namespace:
        t_namespace = _namespace + "::"
    else : 
        t_namespace = " "

    # SerializeToString
    file_cc.write("size_t " + t_namespace + class_name + "::SerializeToString(std::string& str)\n{\n")
    file_cc.write("\tsize_t str_len = OVERALL_STR_LENGTH(")
    for msg_string in _list_message_string:
        if is_frist:
            file_cc.write(msg_string._name + ".size()")
            is_frist = False
        else :
            file_cc.write(", " + msg_string._name + ".size()")
    is_frist = True
    file_cc.write(");\n\tstr.resize(str_len);\n\n")

    for msg_int8 in _list_message_int8:
        file_cc.write("\tADD_TO_STR(" + msg_int8._name +");\n")
    for msg_int16 in _list_message_int16:
        file_cc.write("\tADD_TO_STR(" + msg_int16._name +");\n")
    for msg_int32 in _list_message_int32:
        file_cc.write("\tADD_TO_STR(" + msg_int32._name +");\n")
    for msg_int64 in _list_message_int64:
        file_cc.write("\tADD_TO_STR(" + msg_int64._name +");\n")
    for msg_uint8 in _list_message_uint8:
        file_cc.write("\tADD_TO_STR(" + msg_uint8._name +");\n")
    for msg_uint16 in _list_message_uint16:
        file_cc.write("\tADD_TO_STR(" + msg_uint16._name +");\n")
    for msg_uint32 in _list_message_uint32:
        file_cc.write("\tADD_TO_STR(" + msg_uint32._name +");\n")
    for msg_uint64 in _list_message_uint64:
        file_cc.write("\tADD_TO_STR(" + msg_uint64._name +");\n")
    for msg_bool in _list_message_bool:
        file_cc.write("\tADD_TO_STR(" + msg_bool._name +");\n")
    for msg_float in _list_message_float:
        file_cc.write("\tADD_TO_STR(" + msg_float._name +");\n")
    for msg_double in _list_message_double:
        file_cc.write("\tADD_TO_STR(" + msg_double._name +");\n")
    for msg_enum in _list_message_enum:
        file_cc.write("\tADD_TO_STR(" + msg_enum._name +");\n")
    for msg_string in _list_message_string:
        file_cc.write("\tSTR_ADD_TO_STR(" + msg_string._name +");\n")

    file_cc.write("\n\t_add_len = 0;\n\treturn str_len;\n}\n\n")

    # SerializeToCString
    file_cc.write("char* " + t_namespace + class_name + "::SerializeToCString(size_t& len)\n{\n")
    file_cc.write("\tlen = OVERALL_STR_LENGTH(")
    for msg_string in _list_message_string:
        if is_frist:
            file_cc.write(msg_string._name + ".size()")
            is_frist = False
        else :
            file_cc.write(", " + msg_string._name + ".size()")
    is_frist = True
    file_cc.write(");\n\t_c_data = new char[len];\n\n")

    for msg_int8 in _list_message_int8:
        file_cc.write("\tADD_TO_CSTR(" + msg_int8._name +");\n")
    for msg_int16 in _list_message_int16:
        file_cc.write("\tADD_TO_CSTR(" + msg_int16._name +");\n")
    for msg_int32 in _list_message_int32:
        file_cc.write("\tADD_TO_CSTR(" + msg_int32._name +");\n")
    for msg_int64 in _list_message_int64:
        file_cc.write("\tADD_TO_CSTR(" + msg_int64._name +");\n")
    for msg_uint8 in _list_message_uint8:
        file_cc.write("\tADD_TO_CSTR(" + msg_uint8._name +");\n")
    for msg_uint16 in _list_message_uint16:
        file_cc.write("\tADD_TO_CSTR(" + msg_uint16._name +");\n")
    for msg_uint32 in _list_message_uint32:
        file_cc.write("\tADD_TO_CSTR(" + msg_uint32._name +");\n")
    for msg_uint64 in _list_message_uint64:
        file_cc.write("\tADD_TO_CSTR(" + msg_uint64._name +");\n")
    for msg_bool in _list_message_bool:
        file_cc.write("\tADD_TO_CSTR(" + msg_bool._name +");\n")
    for msg_float in _list_message_float:
        file_cc.write("\tADD_TO_CSTR(" + msg_float._name +");\n")
    for msg_double in _list_message_double:
        file_cc.write("\tADD_TO_CSTR(" + msg_double._name +");\n")
    for msg_enum in _list_message_enum:
        file_cc.write("\tADD_TO_CSTR(" + msg_enum._name +");\n")
    for msg_string in _list_message_string:
        file_cc.write("\tSTR_ADD_TO_CSTR(" + msg_string._name +");\n")

    file_cc.write("\n\t_add_len = 0;\n\treturn _c_data;\n}\n\n")

    # SerializeFromString
    file_cc.write("int " + t_namespace + class_name + "::SerializeFromString(std::string& str)\n{\n")

    for msg_int8 in _list_message_int8:
        file_cc.write("\tPOP_FROM_STR(" + msg_int8._name +");\n")
    for msg_int16 in _list_message_int16:
        file_cc.write("\tPOP_FROM_STR(" + msg_int16._name +");\n")
    for msg_int32 in _list_message_int32:
        file_cc.write("\tPOP_FROM_STR(" + msg_int32._name +");\n")
    for msg_int64 in _list_message_int64:
        file_cc.write("\tPOP_FROM_STR(" + msg_int64._name +");\n")
    for msg_uint8 in _list_message_uint8:
        file_cc.write("\tPOP_FROM_STR(" + msg_uint8._name +");\n")
    for msg_uint16 in _list_message_uint16:
        file_cc.write("\tPOP_FROM_STR(" + msg_uint16._name +");\n")
    for msg_uint32 in _list_message_uint32:
        file_cc.write("\tPOP_FROM_STR(" + msg_uint32._name +");\n")
    for msg_uint64 in _list_message_uint64:
        file_cc.write("\tPOP_FROM_STR(" + msg_uint64._name +");\n")
    for msg_bool in _list_message_bool:
        file_cc.write("\tPOP_FROM_STR(" + msg_bool._name +");\n")
    for msg_float in _list_message_float:
        file_cc.write("\tPOP_FROM_STR(" + msg_float._name +");\n")
    for msg_double in _list_message_double:
        file_cc.write("\tPOP_FROM_STR(" + msg_double._name +");\n")
    for msg_enum in _list_message_enum:
        file_cc.write("\tPOP_FROM_STR(" + msg_enum._name +");\n")
    for msg_string in _list_message_string:
        file_cc.write("\tSTR_POP_FROM_STR(" + msg_string._name +");\n")

    file_cc.write("\n\tIS_STR_ERR();\n\treturn 0;\n}\n\n")

    # SerializeFromCString
    file_cc.write("int " + t_namespace + class_name + "::SerializeFromCString(char* c_str, size_t len)\n{\n")
    file_cc.write("\tstd::string str(c_str, len);\n\treturn SerializeFromString(str);\n}\n\n")

    # achieve msg variable
    if not "" == _namespace:
        for msg_int8 in _list_message_int8:
            file_cc.write("ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_INT8," + msg_int8._name + ", " + class_name + ", " + _namespace +")\n\n")
        for msg_int16 in _list_message_int16:
            file_cc.write("ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_INT16," + msg_int16._name + ", " + class_name + ", " + _namespace +")\n\n")
        for msg_int32 in _list_message_int32:
            file_cc.write("ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_INT32," + msg_int32._name + ", " + class_name + ", " + _namespace +")\n\n")
        for msg_int64 in _list_message_int64:
            file_cc.write("ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_INT64," + msg_int64._name + ", " + class_name + ", " + _namespace +")\n\n")
        for msg_uint8 in _list_message_uint8:
            file_cc.write("ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_UINT8," + msg_uint8._name + ", " + class_name + ", " + _namespace +")\n\n")
        for msg_uint16 in _list_message_uint16:
            file_cc.write("ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_UINT16," + msg_uint16._name + ", " + class_name + ", " + _namespace +")\n\n")
        for msg_uint32 in _list_message_uint32:
            file_cc.write("ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_UINT32," + msg_uint32._name + ", " + class_name + ", " + _namespace +")\n\n")
        for msg_uint64 in _list_message_uint64:
            file_cc.write("ADD_MSG_ACHIEVE_HAVE_NAMESPACE(P_UINT64," + msg_uint64._name + ", " + class_name + ", " + _namespace +")\n\n")
        for msg_bool in _list_message_bool:
            file_cc.write("ADD_MSG_ACHIEVE_HAVE_NAMESPACE(bool," + msg_bool._name + ", " + class_name + ", " + _namespace +")\n\n")
        for msg_float in _list_message_float:
            file_cc.write("ADD_MSG_ACHIEVE_HAVE_NAMESPACE(float," + msg_float._name + ", " + class_name + ", " + _namespace +")\n\n")
        for msg_double in _list_message_double:
            file_cc.write("ADD_MSG_ACHIEVE_HAVE_NAMESPACE(double," + msg_double._name + ", " + class_name + ", " + _namespace +")\n\n")
        for msg_enum in _list_message_enum:
            file_cc.write("ADD_MSG_ENUM_ACHIEVE_HAVE_NAMESPACE(" + msg_enum._type + ", " + msg_enum._name + ", " + class_name + ", " + _namespace +")\n\n")
        for msg_string in _list_message_string:
            file_cc.write("ADD_MSG_STRING_ACHIEVE_HAVE_NAMESPACE(" + msg_string._name + ", " + class_name + ", " + _namespace +")\n\n")
    else :
        for msg_int8 in _list_message_int8:
            file_cc.write("ADD_MSG_ACHIEVE(P_INT8," + msg_int8._name + ", " + class_name + ")\n\n")
        for msg_int16 in _list_message_int16:
            file_cc.write("ADD_MSG_ACHIEVE(P_INT16," + msg_int16._name + ", " + class_name + ")\n\n")
        for msg_int32 in _list_message_int32:
            file_cc.write("ADD_MSG_ACHIEVE(P_INT32," + msg_int32._name + ", " + class_name +")\n\n")
        for msg_int64 in _list_message_int64:
            file_cc.write("ADD_MSG_ACHIEVE(P_INT64," + msg_int64._name + ", " + class_name + ")\n\n")
        for msg_uint8 in _list_message_uint8:
            file_cc.write("ADD_MSG_ACHIEVE(P_UINT8," + msg_uint8._name + ", " + class_name + ")\n\n")
        for msg_uint16 in _list_message_uint16:
            file_cc.write("ADD_MSG_ACHIEVE(P_UINT16," + msg_uint16._name + ", " + class_name +")\n\n")
        for msg_uint32 in _list_message_uint32:
            file_cc.write("ADD_MSG_ACHIEVE(P_UINT32," + msg_uint32._name + ", " + class_name +")\n\n")
        for msg_uint64 in _list_message_uint64:
            file_cc.write("ADD_MSG_ACHIEVE(P_UINT64," + msg_uint64._name + ", " + class_name + ")\n\n")
        for msg_bool in _list_message_bool:
            file_cc.write("ADD_MSG_ACHIEVE(bool," + msg_bool._name + ", " + class_name + ")\n\n")
        for msg_float in _list_message_float:
            file_cc.write("ADD_MSG_ACHIEVE(float," + msg_float._name + ", " + class_name + ")\n\n")
        for msg_double in _list_message_double:
            file_cc.write("ADD_MSG_ACHIEVE(double," + msg_double._name + ", " + class_name + ")\n\n")
        for msg_enum in _list_message_enum:
            file_cc.write("ADD_MSG_ENUM_ACHIEVE(" + msg_enum._type + ", " + msg_bool._name + ", " + class_name + ")\n\n")
        for msg_string in _list_message_string:
            file_cc.write("ADD_MSG_STRING_ACHIEVE(" + msg_string._name + ", " + class_name + ")\n\n")

    return 0




def _start(url:str, file_h, file_cc):
    try:
        _tree = xml_et.parse(url)
    except xml_et.ParseError:
        print(bcolors.FAIL + "this xml file error" + bcolors.ENDC)
        return
    
    _package = _tree.getroot()

    if "name" in _package.attrib:
        global _namespace 
        _namespace = _package.attrib["name"]

    if not "" == _namespace :
        file_h.write("namespace " + _namespace + "\n{\n\n")

    for _class in _package.findall("class"):
        if -1 == _deal_cpp_class(_class, file_h, file_cc):
            return

    if not "" == _namespace :
        file_h.write("} // namespace " + _namespace + "\n\n")
    print(bcolors.OKGREEN + "success" + bcolors.ENDC)






def makefile(out_path : str, file_name : str) :
    file_h = open(out_path + file_name + ".potato.h" , "w")
    file_cc = open(out_path + file_name + ".potato.cc" , "w")
    # file_h.write("#ifndef _" + file_name +"_potato_h\n" + "#define _" + file_name +"_potato_h\n" )
    file_h.write("")
    file_cc.write("")
    file_h.close
    file_cc.close
    file_h = open(out_path + file_name + ".potato.h" , "a")
    file_cc = open(out_path + file_name + ".potato.cc" , "a")
    return file_h,file_cc







def main(argv : list[str]):
    in_file = ""
    out_path = ""

    if([] == argv):
        print(bcolors.FAIL + "error: Please use it correctly" + bcolors.ENDC)
        print("-h  help")
        print("-i  or  --input_file  <input_file>")
        print("-o  or  --output_path  <output_path>")
        return

    try :
        opts, args = getopt.getopt(argv, "hi:o:", ["input_file=", "output_path="])
    except getopt.GetoptError as err:
        print(bcolors.FAIL + err.msg + bcolors.ENDC)
        print("-h  help")
        print("-i  or  --input_file  <input_file>")
        print("-o  or  --output_path  <output_path>")
        return

    for opt,arg in opts:
        if opt == "-h":
            print("-i  or  --input_file  <input_file>")
            print("-o  or  --output_path  <output_path>")
            return
        
        elif opt in ("-i", "--input_file"):
            in_file = arg
        elif opt in ("-o", "--output_path"):
            out_path = arg

    if "" == out_path:
        out_path = "./"
    else :
        if not os.path.exists(out_path) :
            os.makedirs(out_path)
        
    if not out_path.endswith("/") :
        out_path += "/"

    file_name = os.path.basename(in_file).split(".")[0]
    file_h,file_cc = makefile( out_path, file_name )
    
    file_h.write("#ifndef _" + file_name +"_potato_h\n" + "#define _" + file_name +"_potato_h\n\n\n" )
    file_h.write("#include \"stink_potatobuf/stink_potatobuf.h\"\n\n\n")
    file_cc.write("#include \"" + file_name + ".potato.h\"\n\n")
    _start(in_file, file_h, file_cc)
    file_h.write("#endif //" + file_name +"_potato_h\n" )
    file_h.close
    file_cc.close
    






if __name__ == "__main__":
    main(sys.argv[1:])
