\#include "${out_file}.hpp"
\#include "cocos2d_specifics.hpp"
#for header in $headers
\#include "${os.path.basename(header)}"
#end for

template<class T>
static JSBool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	TypeTest<T> t;
#if $script_control_cpp
	T* cobj = new T();
#end if
	js_type_class_t *typeClass = nullptr;
	long typeId = t.s_id();
	auto typeMapIter = _js_global_type_map.find(typeId);
	CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
	typeClass = typeMapIter->second;
	CCASSERT(typeClass, "The value is null.");

	JSObject *_tmp = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
#if $script_control_cpp
	js_proxy_t *pp = jsb_new_proxy(cobj, _tmp);

	JS_AddObjectRoot(cx, &pp->obj);
#end if
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));
	return JS_TRUE;
}

static JSBool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	return JS_FALSE;
}

