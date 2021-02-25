#include <napi.h>
#include <thread>
#include <iostream>
#include <chrono>

void t1() {
  for (int i = 0; i < 19; i++) {
    std::cout << "t11111111\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1 + rand() % 10));
  }
}

int add(int&& a, int&& b) {
  return a + b;
}

void t2() {
  for (int i = 0; i < 19; i++) {
    std::cout << "t222222222\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1 + rand() % 10));
  }
}

std::string hello(){
  std::thread th1(t1);
  std::thread th2(t2);

  th1.join();
  th2.join();

  return "here is main end\n";
}

Napi::String helloWrap(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::String returnValue = Napi::String::New(env, hello());

  return returnValue;
}

Napi::Number addWrap(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  if (info.Length() < 2) {
    Napi::TypeError::New(env, "Number Error").ThrowAsJavaScriptException();
  }

  Napi::Number a = info[0].As<Napi::Number>();
  Napi::Number b = info[1].As<Napi::Number>();

  int returnValue = add(a.Int32Value(), b.Int32Value());

  return Napi::Number::New(env, returnValue);
}

Napi::Object Init(Napi::Env env, Napi::Object exports){
  exports.Set("hello", Napi::Function::New(env, helloWrap));
  exports.Set("add", Napi::Function::New(env, addWrap));

  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init);
