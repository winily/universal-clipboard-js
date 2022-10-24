#pragma once
#include <napi.h>

#include "util.hpp"

#ifdef __APPLE__
#include "mac.h"
#endif

Napi::Value Read(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  if (info.Length() < 1) {
    Napi::Error::New(env, "wrong number of arguments")
        .ThrowAsJavaScriptException();
    return env.Undefined();
  }
  if (!info[0].IsString()) {
    Napi::Error::New(env, "string expected").ThrowAsJavaScriptException();
    return env.Undefined();
  }
  auto format = GetStringArg(info, 0, env);

#ifdef __APPLE__
  return Read_Impl(format, env);
#endif

  return info.Env().Undefined();
}

Napi::Value Write(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  if (info.Length() < 2) {
    Napi::Error::New(env, "wrong number of arguments")
        .ThrowAsJavaScriptException();
    return env.Undefined();
  }
  if (!info[0].IsString() || !info[1].IsObject()) {
    Napi::Error::New(
        env, "arguments type does not match (format: string, buf: Buffer)")
        .ThrowAsJavaScriptException();
    return env.Undefined();
  }

  auto format = GetStringArg(info, 0, env);
  auto buffer = GetBufferArg(info, 1, env);
  return Write_Impl(format, buffer, env);
}

Napi::Value Clear(const Napi::CallbackInfo &info) {
  return Clear_Impl(info.Env());
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports["read"] = Napi::Function::New(env, Read);
  exports["write"] = Napi::Function::New(env, Write);
  exports["clear"] = Napi::Function::New(env, Clear);
  return exports;
}
