/*
 * Copyright (C) 2011 by Jakub Lekstan <kuebzky@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <v8.h>
#include <node.h>

#define NODE_DEFINE_NAMED_CONSTANT(target, name, constant) \
    (target)->Set(v8::String::NewSymbol(name), \
                  v8::Integer::New(constant), \
                  static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete))

static v8::Handle<v8::Value> getStack(const v8::Arguments& args){
    v8::HandleScope scope;

    int frameCount = 10;
    int stackOptions = v8::StackTrace::kOverview;

    if (args.Length() <= 2 && args[0]->IsNumber()) {
        frameCount = (int) v8::Local<v8::Integer>::Cast(args[0])->Int32Value();
    }

    if (args.Length() == 2 && args[1]->IsNumber()) {
        stackOptions = (int) v8::Local<v8::Integer>::Cast(args[1])->Int32Value();
    }

    v8::Local<v8::StackTrace> currentStack = v8::StackTrace::CurrentStackTrace(frameCount, static_cast<v8::StackTrace::StackTraceOptions>(stackOptions));

    return scope.Close(currentStack->AsArray());
}

void init (v8::Handle<v8::Object> target){
    v8::HandleScope scope;

    NODE_SET_METHOD(target, "getStack", getStack);
    NODE_DEFINE_NAMED_CONSTANT(target, "kLineNumber", v8::StackTrace::kLineNumber);
    NODE_DEFINE_NAMED_CONSTANT(target, "kColumnOffset", v8::StackTrace::kColumnOffset);
    NODE_DEFINE_NAMED_CONSTANT(target, "kScriptName", v8::StackTrace::kScriptName);
    NODE_DEFINE_NAMED_CONSTANT(target, "kFunctionName", v8::StackTrace::kFunctionName);
    NODE_DEFINE_NAMED_CONSTANT(target, "kIsEval", v8::StackTrace::kIsEval);
    NODE_DEFINE_NAMED_CONSTANT(target, "kIsConstructor", v8::StackTrace::kIsConstructor);
    NODE_DEFINE_NAMED_CONSTANT(target, "kScriptNameOrSourceURL", v8::StackTrace::kScriptNameOrSourceURL);
    NODE_DEFINE_NAMED_CONSTANT(target, "kOverview", v8::StackTrace::kOverview);
    NODE_DEFINE_NAMED_CONSTANT(target, "kDetailed", v8::StackTrace::kDetailed);
}

NODE_MODULE(stack, init);
