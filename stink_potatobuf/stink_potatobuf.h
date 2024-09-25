#ifndef S_POTATOBUF
#define S_POTATOBUF

#include <string>
#include <cstdarg>


#define ERROR_STR "The byte stream does not match this type of structure \n"
#define EQUAL(TYPE1, TYPE2) std::string(#TYPE1) == std::string(#TYPE2)

#define INIT_MSG_NUM(	num_int8,		\
						num_int16,		\
						num_int32,		\
						num_int64,		\
						num_uint8,		\
						num_uint16,		\
						num_uint32,		\
						num_uint64,		\
						num_bool,		\
						num_float,		\
						num_double,		\
						num_enum,		\
						num_string)		\
				_num[0] = num_int8;		\
				_num[1] = num_int16;	\
				_num[2] = num_int32;	\
				_num[3] = num_int64;	\
				_num[4] = num_uint8;	\
				_num[5] = num_uint16;	\
				_num[6] = num_uint32;	\
				_num[7] = num_uint64;	\
				_num[8] = num_bool;		\
				_num[9] = num_float;	\
				_num[10] = num_double;	\
				_num[11] = num_enum;	\
				_num[12] = num_string;		

#define OVERALL_STR_LENGTH(...)		\
				_over_all_length(_num[_num_string], __VA_ARGS__)
				
#define ADD_TO_STR(name)		\
				char* _x_##name = (char*)&name;				\
				for(size_t i = 0; i < sizeof(name); ++i){	\
					str[_add_len + i] = _x_##name[i];}		\
				_add_len += sizeof(name);

#define  STR_ADD_TO_STR(name)		\
				size_t name##_size = name.size();			\
				ADD_TO_STR(name##_size)					\
				for (size_t i = 0; i < name.size(); ++i)	\
				{											\
					str[_add_len + i] = name[i];			\
				}											\
				_add_len += name.size();				

#define ADD_TO_CSTR(name)		\
				char* _x_##name = (char*)&name;				\
				for(size_t i = 0; i < sizeof(name); ++i){	\
					_c_data[_add_len + i] = _x_##name[i];}	\
				_add_len += sizeof(name);

#define  STR_ADD_TO_CSTR(name)		\
				size_t name##_size = name.size();			\
				ADD_TO_CSTR(name##_size)					\
				for (size_t i = 0; i < name.size(); ++i)	\
				{											\
					_c_data[_add_len + i] = name[i];		\
				}											\
				_add_len += name.size();				

#define POP_FROM_STR(name)		\
				size_t need_size##name =_pop_len + sizeof(name);	\
				if(need_size##name > str.size()){					\
					_pop_len = 0;								\
					_error = std::string(ERROR_STR);		\
					return -1;}									\
				char* _x_##name = (char*)&name;				\
				for (size_t i = 0; i < sizeof(name); ++i)	\
				{											\
					_x_##name[i] = str[_pop_len + i];		\
				}											\
				_pop_len += sizeof(name);

#define  STR_POP_FROM_STR(name)		\
				size_t name##_size = 0;						\
				POP_FROM_STR(name##_size)					\
				size_t need_size##name =_pop_len + name##_size;	\
				if(need_size##name > str.size()){					\
					_pop_len = 0;								\
					_error = std::string(ERROR_STR);		\
					return -1;}									\
				name.resize(name##_size);					\
				for (size_t i = 0; i < name##_size; ++i)	\
				{											\
					name[i] = str[_pop_len + i];			\
				}											\
				_pop_len += name.size();				

#define POP_FROM_CSTR(name)		\
				size_t need_size##name =_pop_len + sizeof(name);	\
				if(need_size##name > len){					\
					_pop_len = 0;								\
					_error = std::string(ERROR_STR);		\
					return -1;}									\
				char* _x_##name = (char*)&name;				\
				for(size_t i = 0; i < sizeof(name); ++i){	\
					_x_##name[i] = c_str[_add_len + i];}	\
				_pop_len += sizeof(name);

#define  STR_POP_FROM_CSTR(name)		\
				size_t name##_size = 0;						\
				POP_FROM_CSTR(name##_size)					\
				size_t need_size##name =_pop_len + name##_size;	\
				if(need_size##name > len){					\
					_pop_len = 0;								\
					_error = std::string(ERROR_STR);		\
					return -1;}									\
				name.resize(name##_size);					\
				for (size_t i = 0; i < name##_size; ++i)	\
				{											\
					name[i] = c_str[_pop_len + i];			\
				}											\
				_pop_len += name.size();				

#define IS_STR_ERR()		\
				if (_pop_len < str.size())			\
				{									\
					_pop_len = 0;					\
					_error = std::string(ERROR_STR);		\
					return -1;						\
				}									\
				_pop_len = 0;

#define IS_CSTR_ERR()		\
				if (_pop_len < len)			\
				{									\
					_pop_len = 0;					\
					_error = std::string(ERROR_STR);		\
					return -1;						\
				}									\
				_pop_len = 0;

// .h
// P_INT8// P_INT16// P_INT32// P_INT64
// P_UINT8// P_UINT16// P_UINT32// P_UINT64
// bool// float// double
#define ADD_MSG(T, msg_name)		\
				T get_##msg_name();			\
				void set_##msg_name(T value);	\
				void clear_##msg_name();

//.cc
// P_INT8// P_INT16// P_INT32// P_INT64
// P_UINT8// P_UINT16// P_UINT32// P_UINT64
// bool// float// double
#define ADD_MSG_ACHIEVE(T, msg_name, class_name)		\
				T class_name::get_##msg_name()		\
				{												\
					return msg_name;									\
				}												\
				void class_name::set_##msg_name(T value)	\
				{												\
					msg_name = value;								\
				}												\
				void class_name::clear_##msg_name()				\
				{												\
					if(EQUAL(bool, T))							\
					{											\
						msg_name = false;						\
					}											\
					if(EQUAL(float, T))							\
					{											\
						msg_name = 0.0f;						\
					}											\
					if(EQUAL(double, T))						\
					{											\
						msg_name = 0.0;							\
					}											\
					msg_name = 0;								\
				}

//.cc
// P_INT8// P_INT16// P_INT32// P_INT64
// P_UINT8// P_UINT16// P_UINT32// P_UINT64
// bool// float// double
#define ADD_MSG_ACHIEVE_HAVE_NAMESPACE(T, msg_name, class_name, namespace_name)	\
				T namespace_name::class_name::get_##msg_name()		\
				{												\
					return msg_name;									\
				}												\
				void namespace_name::class_name::set_##msg_name(T value)	\
				{												\
					msg_name = value;								\
				}												\
				void namespace_name::class_name::clear_##msg_name()				\
				{												\
					if(EQUAL(bool, T))							\
					{											\
						msg_name = false;						\
					}											\
					if(EQUAL(float, T))							\
					{											\
						msg_name = 0.0f;						\
					}											\
					if(EQUAL(double, T))						\
					{											\
						msg_name = 0.0;							\
					}											\
					msg_name = 0;								\
				}

//.h
// #enum name
#define ADD_MSG_ENUM(enum_nmae, msg_name)		ADD_MSG(enum_nmae, msg_name)

//.cc
// #enum name
#define ADD_MSG_ENUM_ACHIEVE(enum_nmae, msg_name, class_name)	\
				class_name::enum_nmae class_name::get_##msg_name()		\
				{												\
					return msg_name;									\
				}												\
				void class_name::set_##msg_name(enum_nmae value)	\
				{												\
					msg_name = value;								\
				}												\
				void class_name::clear_##msg_name()				\
				{												\
					msg_name = class_name::enum_nmae(0);									\
				}

//.cc
// #enum name
#define ADD_MSG_ENUM_ACHIEVE_HAVE_NAMESPACE(enum_nmae, msg_name, class_name, namespace_name)	\
				namespace_name::class_name::enum_nmae namespace_name::class_name::get_##msg_name()		\
				{												\
					return msg_name;									\
				}												\
				void namespace_name::class_name::set_##msg_name(enum_nmae value)	\
				{												\
					msg_name = value;								\
				}												\
				void namespace_name::class_name::clear_##msg_name()				\
				{												\
					msg_name = namespace_name::class_name::enum_nmae(0);									\
				}

//.h
// std::string
#define ADD_MSG_STRING(msg_name)		\
				const std::string& get_##msg_name();				\
				void set_##msg_name(const std::string& value);		\
				void set_##msg_name(const char* value);				\
				void set_##msg_name(const char* value, size_t size);	\
				void clear_##msg_name();							

//.cc
// std::string
#define ADD_MSG_STRING_ACHIEVE(msg_name, class_name)	\
				const std::string& class_name::get_##msg_name()		\
				{												\
					return msg_name;									\
				}												\
				void class_name::set_##msg_name(const std::string& value)	\
				{												\
					msg_name = value;								\
				}												\
				void class_name::set_##msg_name(const char* value)	\
				{												\
					msg_name = value;								\
				}												\
				void class_name::set_##msg_name(const char* value, size_t size)	\
				{												\
					msg_name.resize(size);						\
					for (size_t i = 0; i < size; ++i)			\
					{											\
						msg_name[i] = value[i];					\
					}											\
				}												\
				void class_name::clear_##msg_name()				\
				{												\
					msg_name.clear();									\
				}

//.cc
// std::string
#define ADD_MSG_STRING_ACHIEVE_HAVE_NAMESPACE(msg_name, class_name, namespace_name)	\
				const std::string& namespace_name::class_name::get_##msg_name()		\
				{												\
					return msg_name;									\
				}												\
				void namespace_name::class_name::set_##msg_name(const std::string& value)	\
				{												\
					msg_name = value;								\
				}												\
				void namespace_name::class_name::set_##msg_name(const char* value)	\
				{												\
					msg_name = value;								\
				}												\
				void namespace_name::class_name::set_##msg_name(const char* value, size_t size)	\
				{												\
					msg_name.resize(size);						\
					for (size_t i = 0; i < size; ++i)			\
					{											\
						msg_name[i] = value[i];					\
					}											\
				}												\
				void namespace_name::class_name::clear_##msg_name()				\
				{												\
					msg_name.clear();									\
				}


#define TYPE_SIZE 13

typedef		char				P_INT8;
typedef		short				P_INT16;
typedef		int					P_INT32;
typedef		long long			P_INT64;
typedef		unsigned char		P_UINT8;
typedef		unsigned short		P_UINT16;
typedef		unsigned int		P_UINT32;
typedef		unsigned long long	P_UINT64;


namespace PotatoBuffer
{


class _potatobuf 
{
public:
	_potatobuf() :
		_c_data(nullptr),
		_num(new size_t[TYPE_SIZE]),
		_add_len(0),
		_pop_len(0),
		_error(std::string("not error \n"))
	{

		
	}

	virtual ~_potatobuf()
	{
		if (_c_data)
		{
			delete[] _c_data;
			_c_data = nullptr;
		}
		if (_num)
		{
			delete[] _num;
			_num = nullptr;
		}
	}

	virtual size_t SerializeToString(std::string&) = 0;
	//返回的指针将在调用析构函数后失效
	virtual char* SerializeToCString(size_t&) = 0;
	virtual int SerializeFromString(std::string&) = 0;
	virtual int SerializeFromCString(char*, size_t) = 0;

	std::string& get_error()
	{
		return _error;
	}

protected:
	std::string _error;
	char* _c_data;
	//
	size_t _add_len;
	size_t _pop_len;

	enum : int
	{
		_num_int8,
		_num_int16,
		_num_int32,
		_num_int64,
		_num_uint8,
		_num_uint16,
		_num_uint32,
		_num_uint64,
		_num_bool,
		_num_float,
		_num_double,
		_num_enum,
		_num_string
	};
	
	size_t* _num;

	size_t _sum()
	{
		size_t sum = 0;
		sum += _num[_num_int8] * sizeof(P_INT8);
		sum += _num[_num_int16] * sizeof(P_INT16);
		sum += _num[_num_int32] * sizeof(P_INT32);
		sum += _num[_num_int64] * sizeof(P_INT64);
		sum += _num[_num_uint8] * sizeof(P_UINT8);
		sum += _num[_num_uint16] * sizeof(P_UINT16);
		sum += _num[_num_uint32] * sizeof(P_UINT32);
		sum += _num[_num_uint64] * sizeof(P_UINT64);

		sum += _num[_num_bool] * sizeof(bool);
		sum += _num[_num_float] * sizeof(float);
		sum += _num[_num_double] * sizeof(double);
		sum += _num[_num_enum] * sizeof(int);

		return sum;
	}

	size_t _over_all_length(int str_num, ...)
	{
		size_t str_len = _sum();

		if (0 == str_num)
		{
			return str_len;
		}

		va_list args;
		va_start(args, str_num);
		for (int i = 0; i < str_num; ++i)
		{
			str_len += sizeof(size_t);
			str_len += va_arg(args, int);
		}
		va_end(args);
		return str_len;
	}
};

} // namespace PoatatoBuffer




#endif // !S_POTATOBUF

