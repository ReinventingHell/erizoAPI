#define BUILDING_NODE_EXTENSION
#include <node.h>
#include "OneToManyProcessor.h"


using namespace v8;

OneToManyProcessor::OneToManyProcessor() {};
OneToManyProcessor::~OneToManyProcessor() {};

void OneToManyProcessor::Init(Handle<Object> target) {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("OneToManyProcessor"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  // Prototype
  tpl->PrototypeTemplate()->Set(String::NewSymbol("close"), FunctionTemplate::New(close)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setPublisher"), FunctionTemplate::New(setPublisher)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("hasPublisher"), FunctionTemplate::New(hasPublisher)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("addSubscriber"), FunctionTemplate::New(addSubscriber)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("removeSubscriber"), FunctionTemplate::New(removeSubscriber)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("sendFIR"), FunctionTemplate::New(sendFIR)->GetFunction());

  Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
  target->Set(String::NewSymbol("OneToManyProcessor"), constructor);
}

Handle<Value> OneToManyProcessor::New(const Arguments& args) {
  HandleScope scope;

  OneToManyProcessor* obj = new OneToManyProcessor();
  obj->me = new erizo::OneToManyProcessor();

  obj->Wrap(args.This());

  return args.This();
}

Handle<Value> OneToManyProcessor::close(const Arguments& args) {
  HandleScope scope;

  OneToManyProcessor* obj = ObjectWrap::Unwrap<OneToManyProcessor>(args.This());
  erizo::OneToManyProcessor *me = (erizo::OneToManyProcessor*)obj->me;

  delete me;

  return scope.Close(Null());
}

Handle<Value> OneToManyProcessor::setPublisher(const Arguments& args) {
  HandleScope scope;

  OneToManyProcessor* obj = ObjectWrap::Unwrap<OneToManyProcessor>(args.This());
  erizo::OneToManyProcessor *me = (erizo::OneToManyProcessor*)obj->me;

  WebRtcConnection* param = ObjectWrap::Unwrap<WebRtcConnection>(args[0]->ToObject());
  erizo::WebRtcConnection *wr = param->me;

  me->setPublisher(wr);

  return scope.Close(Null());
}

Handle<Value> OneToManyProcessor::hasPublisher(const Arguments& args) {
  HandleScope scope;

  OneToManyProcessor* obj = ObjectWrap::Unwrap<OneToManyProcessor>(args.This());
  erizo::OneToManyProcessor *me = (erizo::OneToManyProcessor*)obj->me;

  bool p = true;

  if(me->publisher == NULL) {
    p = false;
  }
  
  return scope.Close(Boolean::New(p));
}

Handle<Value> OneToManyProcessor::addSubscriber(const Arguments& args) {
  HandleScope scope;

  OneToManyProcessor* obj = ObjectWrap::Unwrap<OneToManyProcessor>(args.This());
  erizo::OneToManyProcessor *me = (erizo::OneToManyProcessor*)obj->me;

  WebRtcConnection* param = ObjectWrap::Unwrap<WebRtcConnection>(args[0]->ToObject());
  erizo::WebRtcConnection *wr = param->me;

  int peerId = args[1]->IntegerValue(); 

  me->addSubscriber(wr, peerId);

  return scope.Close(Null());
}

Handle<Value> OneToManyProcessor::removeSubscriber(const Arguments& args) {
  HandleScope scope;

  OneToManyProcessor* obj = ObjectWrap::Unwrap<OneToManyProcessor>(args.This());
  erizo::OneToManyProcessor *me = (erizo::OneToManyProcessor*)obj->me;

  int peerId = args[0]->IntegerValue(); 

  me->removeSubscriber(peerId);

  return scope.Close(Null());
}

Handle<Value> OneToManyProcessor::sendFIR(const Arguments& args) {
  HandleScope scope;

  OneToManyProcessor* obj = ObjectWrap::Unwrap<OneToManyProcessor>(args.This());
  erizo::OneToManyProcessor *me = (erizo::OneToManyProcessor*)obj->me;

  me->publisher->sendFirPacket();
  
  return scope.Close(Null());
}