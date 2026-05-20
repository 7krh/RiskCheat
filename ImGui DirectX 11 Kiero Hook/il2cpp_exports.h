#pragma once
#include <Windows.h>
#include <cstdint>
#include <cstring>

namespace il2cpp_exp
{
    typedef void*       (__stdcall* t_domain_get)();
    typedef void**      (__cdecl*   t_domain_get_assemblies)(void* domain, size_t* size);
    typedef void*       (__stdcall* t_assembly_get_image)(void* assembly);
    typedef void*       (__stdcall* t_class_from_name)(void* image, const char* name_space, const char* name);
    typedef void        (__stdcall* t_runtime_class_init)(void* klass);
    typedef void*       (__stdcall* t_class_get_methods)(void* klass, void** iter);
    typedef void*       (__stdcall* t_class_get_fields)(void* klass, void** iter);
    typedef const char* (__stdcall* t_method_get_name)(void* method);
    typedef int         (__stdcall* t_method_get_param_count)(void* method);
    typedef const char* (__stdcall* t_method_get_param_name)(void* method, uint32_t index);
    typedef int         (__stdcall* t_field_get_offset)(void* field);
    typedef void        (__stdcall* t_field_static_get_value)(void* field, void* value);
    typedef void        (__stdcall* t_field_static_set_value)(void* field, void* value);
    typedef void*       (__stdcall* t_object_get_class)(void* obj);
    typedef const char* (__stdcall* t_class_get_name)(void* klass);
    typedef void*       (__stdcall* t_string_new)(const char* str);
    typedef uint32_t    (__stdcall* t_array_length)(void* arr);
    typedef void*       (__stdcall* t_class_get_element_class)(void* klass);
    typedef int32_t     (__stdcall* t_class_value_size)(void* klass, uint32_t* align);
    typedef bool        (__stdcall* t_class_is_valuetype)(void* klass);
    typedef void*       (__stdcall* t_class_get_field_from_name)(void* klass, const char* name);

    inline t_domain_get             domain_get             = nullptr;
    inline t_domain_get_assemblies  domain_get_assemblies  = nullptr;
    inline t_assembly_get_image     assembly_get_image     = nullptr;
    inline t_class_from_name        class_from_name        = nullptr;
    inline t_runtime_class_init     runtime_class_init     = nullptr;
    inline t_class_get_methods      class_get_methods      = nullptr;
    inline t_class_get_fields       class_get_fields       = nullptr;
    inline t_method_get_name        method_get_name        = nullptr;
    inline t_method_get_param_count method_get_param_count = nullptr;
    inline t_method_get_param_name  method_get_param_name  = nullptr;
    inline t_field_get_offset       field_get_offset       = nullptr;
    inline t_field_static_get_value field_static_get_value = nullptr;
    inline t_field_static_set_value field_static_set_value = nullptr;
    inline t_object_get_class       object_get_class       = nullptr;
    inline t_class_get_name         class_get_name         = nullptr;
    inline t_string_new             string_new             = nullptr;
    inline t_array_length           array_length           = nullptr;
    inline t_class_get_element_class class_get_element_class = nullptr;
    inline t_class_value_size       class_value_size       = nullptr;
    inline t_class_is_valuetype     class_is_valuetype     = nullptr;
    inline t_class_get_field_from_name class_get_field_from_name = nullptr;

    inline bool init()
    {
        HMODULE m = GetModuleHandleA("GameAssembly.dll");
        if (!m) return false;

        domain_get             = (t_domain_get)            GetProcAddress(m, "il2cpp_domain_get");
        domain_get_assemblies  = (t_domain_get_assemblies) GetProcAddress(m, "il2cpp_domain_get_assemblies");
        assembly_get_image     = (t_assembly_get_image)    GetProcAddress(m, "il2cpp_assembly_get_image");
        class_from_name        = (t_class_from_name)       GetProcAddress(m, "il2cpp_class_from_name");
        runtime_class_init     = (t_runtime_class_init)    GetProcAddress(m, "il2cpp_runtime_class_init");
        class_get_methods      = (t_class_get_methods)     GetProcAddress(m, "il2cpp_class_get_methods");
        class_get_fields       = (t_class_get_fields)      GetProcAddress(m, "il2cpp_class_get_fields");
        method_get_name        = (t_method_get_name)       GetProcAddress(m, "il2cpp_method_get_name");
        method_get_param_count = (t_method_get_param_count)GetProcAddress(m, "il2cpp_method_get_param_count");
        method_get_param_name  = (t_method_get_param_name) GetProcAddress(m, "il2cpp_method_get_param_name");
        field_get_offset       = (t_field_get_offset)      GetProcAddress(m, "il2cpp_field_get_offset");
        field_static_get_value = (t_field_static_get_value)GetProcAddress(m, "il2cpp_field_static_get_value");
        field_static_set_value = (t_field_static_set_value)GetProcAddress(m, "il2cpp_field_static_set_value");
        object_get_class       = (t_object_get_class)      GetProcAddress(m, "il2cpp_object_get_class");
        class_get_name         = (t_class_get_name)        GetProcAddress(m, "il2cpp_class_get_name");
        string_new             = (t_string_new)            GetProcAddress(m, "il2cpp_string_new");
        array_length           = (t_array_length)          GetProcAddress(m, "il2cpp_array_length");
        class_get_element_class = (t_class_get_element_class)GetProcAddress(m, "il2cpp_class_get_element_class");
        class_value_size       = (t_class_value_size)      GetProcAddress(m, "il2cpp_class_value_size");
        class_is_valuetype     = (t_class_is_valuetype)    GetProcAddress(m, "il2cpp_class_is_valuetype");
        class_get_field_from_name = (t_class_get_field_from_name)GetProcAddress(m, "il2cpp_class_get_field_from_name");

        return domain_get && domain_get_assemblies && assembly_get_image && class_from_name &&
               runtime_class_init && class_get_methods && class_get_fields &&
               method_get_name && method_get_param_count && method_get_param_name && field_get_offset &&
               object_get_class && class_get_name && string_new && array_length &&
               class_get_element_class && class_value_size && class_is_valuetype && class_get_field_from_name;
    }

    inline void* find_class(const char* name, const char* name_space = "")
    {
        if (!domain_get || !domain_get_assemblies || !assembly_get_image || !class_from_name)
            return nullptr;

        void* domain = domain_get();
        if (!domain) return nullptr;

        size_t count = 0;
        void** assemblies = domain_get_assemblies(domain, &count);
        if (!assemblies || count == 0) return nullptr;

        for (size_t i = 0; i < count; ++i)
        {
            void* img = assembly_get_image(assemblies[i]);
            if (!img) continue;

            void* kl = class_from_name(img, name_space, name);
            if (kl) return kl;
        }
        return nullptr;
    }

    inline void* find_method(const char* class_name,
                             const char* method_name,
                             int param_count_filter = -1,
                             const char* param_name = nullptr,
                             int param_index = -1,
                             const char* name_space = "")
    {
        void* klass = find_class(class_name, name_space);
        if (!klass) return nullptr;

        void* iter = nullptr;
        void* m = nullptr;
        while ((m = class_get_methods(klass, &iter)) != nullptr)
        {
            const char* mname = method_get_name(m);
            if (!mname || strcmp(mname, method_name) != 0) continue;

            if (param_count_filter >= 0 && method_get_param_count(m) != param_count_filter)
                continue;

            if (param_name && param_index >= 0)
            {
                if (param_index >= method_get_param_count(m)) continue;
                const char* pname = method_get_param_name(m, (uint32_t)param_index);
                if (!pname || strcmp(pname, param_name) != 0) continue;
            }

            return *reinterpret_cast<void**>(m);
        }
        return nullptr;
    }

    inline void* find_field(void* klass, const char* field_name)
    {
        if (!klass || !field_name) return nullptr;
        if (class_get_field_from_name) {
            if (void* f = class_get_field_from_name(klass, field_name))
                return f;
        }
        if (class_get_fields) {
            void* iter = nullptr;
            void* f = nullptr;
            while ((f = class_get_fields(klass, &iter)) != nullptr) {
                const char* fname = *reinterpret_cast<const char**>(f);
                if (fname && strcmp(fname, field_name) == 0)
                    return f;
            }
        }
        return nullptr;
    }

    inline int find_field_offset(void* klass, const char* field_name)
    {
        void* f = find_field(klass, field_name);
        if (!f || !field_get_offset) return -1;
        return field_get_offset(f);
    }
}
