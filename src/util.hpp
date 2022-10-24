#pragma once
#include <napi.h>

std::string GetStringArg(const Napi::CallbackInfo &info, int index,
                         Napi::Env env) {
  if (info.Length() < index + 1) {
    Napi::Error::New(env, "wrong number of arguments")
        .ThrowAsJavaScriptException();
    return "";
  }
  Napi::String s = info[index].ToString();
  std::string valInStdString(s);
  return valInStdString;
}

Napi::Buffer<uint8_t> GetBufferArg(const Napi::CallbackInfo &info, int index,
                                   Napi::Env env) {
  if (info.Length() < index + 1) {
    Napi::Error::New(env, "wrong number of arguments")
        .ThrowAsJavaScriptException();
    return Napi::Buffer<uint8_t>();
  }
  Napi::Buffer<uint8_t> buffer = info[index].As<Napi::Buffer<uint8_t>>();
  return buffer;
}
