#pragma once
#include <napi.h>

Napi::Value Read_Impl(std::string format, Napi::Env env);
Napi::Value Write_Impl(std::string format_str, Napi::Buffer<uint8_t> buffer, Napi::Env env);
Napi::Value Clear_Impl(Napi::Env env);