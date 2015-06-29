#include <node.h>
#include <v8.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

using namespace v8;

class Matrix : public node::ObjectWrap {
  public:
    static void Init(Handle<Object> exports) {
      Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
      tpl->SetClassName(String::NewSymbol("Matrix"));
      tpl->InstanceTemplate()->SetInternalFieldCount(2);
      tpl->PrototypeTemplate()->Set(
        String::NewSymbol("addScaledRow"),
        FunctionTemplate::New(addScaledRow)->GetFunction()
      );
      tpl->PrototypeTemplate()->Set(
        String::NewSymbol("get"),
        FunctionTemplate::New(get)->GetFunction()
      );
      tpl->PrototypeTemplate()->Set(
        String::NewSymbol("innerProduct"),
        FunctionTemplate::New(innerProduct)->GetFunction()
      );
      tpl->PrototypeTemplate()->Set(
        String::NewSymbol("scale"),
        FunctionTemplate::New(scale)->GetFunction()
      );
      tpl->PrototypeTemplate()->Set(
        String::NewSymbol("set"),
        FunctionTemplate::New(set)->GetFunction()
      );
      tpl->PrototypeTemplate()->Set(
        String::NewSymbol("setAll"),
        FunctionTemplate::New(setAll)->GetFunction()
      );
      tpl->PrototypeTemplate()->Set(
        String::NewSymbol("setRow"),
        FunctionTemplate::New(setRow)->GetFunction()
      );

      Persistent<Function> constructor =
        Persistent<Function>::New(tpl->GetFunction());
      exports->Set(
        String::NewSymbol("Matrix"),
        constructor
      );
    }

    static Handle<Value> addScaledRow(const Arguments& args) {
      HandleScope scope;
      Matrix* obj = ObjectWrap::Unwrap<Matrix>(args.This());
      Matrix* otherObj = ObjectWrap::Unwrap<Matrix>(args[1]->ToObject());
      gsl_vector_view thisRow = gsl_matrix_row(
        obj->_gsl_handle,
        args[0]->NumberValue()
      );
      gsl_vector_view otherRow = gsl_matrix_row(
        otherObj->_gsl_handle,
        args[2]->IsUndefined() ? 0 : args[2]->NumberValue()
      );
      gsl_blas_daxpy(
        args[3]->IsUndefined() ? 1.0 : args[3]->NumberValue(),
        &otherRow.vector,
        &thisRow.vector
      );
      return args.This();
    }

    static Handle<Value> get(const Arguments& args) {
      HandleScope scope;
      Matrix* obj = ObjectWrap::Unwrap<Matrix>(args.This());
      double val = gsl_matrix_get(
        obj->_gsl_handle,
        args[0]->NumberValue(),
        args[1]->NumberValue()
      );
      return scope.Close(Number::New(val));
    }

    static Handle<Value> innerProduct(const Arguments& args) {
      HandleScope scope;
      Matrix* obj = ObjectWrap::Unwrap<Matrix>(args.This());
      Matrix* otherObj = ObjectWrap::Unwrap<Matrix>(args[1]->ToObject());
      double val;
      gsl_vector_view thisRow = gsl_matrix_row(
        obj->_gsl_handle,
        args[0]->NumberValue()
      );
      gsl_vector_view otherRow = gsl_matrix_row(
        otherObj->_gsl_handle,
        args[2]->IsUndefined() ? 0 : args[2]->NumberValue()
      );
      gsl_blas_ddot(
        &thisRow.vector,
        &otherRow.vector,
        &val
      );
      return scope.Close(Number::New(val));
    }

    static Handle<Value> scale(const Arguments& args) {
      HandleScope scope;
      Matrix* obj = ObjectWrap::Unwrap<Matrix>(args.This());
      gsl_matrix_scale(
        obj->_gsl_handle,
        args[0]->NumberValue()
      );
      return args.This();
    }

    static Handle<Value> set(const Arguments& args) {
      HandleScope scope;
      Matrix* obj = ObjectWrap::Unwrap<Matrix>(args.This());
      gsl_matrix_set(
        obj->_gsl_handle,
        args[0]->NumberValue(),
        args[1]->NumberValue(),
        args[2]->NumberValue()
      );
      return args.This();
    }

    static Handle<Value> setAll(const Arguments& args) {
      HandleScope scope;
      Matrix* obj = ObjectWrap::Unwrap<Matrix>(args.This());
      gsl_matrix_set_all(
        obj->_gsl_handle,
        args[0]->NumberValue()
      );
      return args.This();
    }

    static Handle<Value> setRow(const Arguments& args) {
      HandleScope scope;
      Matrix* obj = ObjectWrap::Unwrap<Matrix>(args.This());
      gsl_vector_view view = gsl_matrix_row(
        obj->_gsl_handle,
        args[0]->NumberValue()
      );
      gsl_vector_set_all(&view.vector, args[1]->NumberValue());
      return args.This();
    }

  private:
    explicit Matrix(size_t n1, size_t n2) {
      _gsl_handle = gsl_matrix_alloc(n1, n2);
    }

    ~Matrix() {
      gsl_matrix_free(_gsl_handle);
    }

    static Handle<Value> New(const Arguments& args) {
      HandleScope handle_scope;
      Matrix* obj = new Matrix(
        args[0]->NumberValue(),
        args[1]->NumberValue()
      );
      obj->Wrap(args.This());
      return args.This();
    }

    gsl_matrix* _gsl_handle;
};

void init(Handle<Object> target) {
  Matrix::Init(target);
}

NODE_MODULE(binding, init);
