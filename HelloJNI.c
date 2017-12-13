#include <stdio.h>
#include <jni.h>

#define NELEM(x) (sizeof(x) / sizeof((x)[0]))
/* #define JNI_CLASS "HelloJNI" */
#define JNI_CLASS "TestJNIPrimitive"

static void native_sayhello(JNIEnv *env, jclass cls)
{
    printf("hello world!\n");
}

static jdouble native_average(JNIEnv *env ,jobject obj, jint n1, jint n2)
{
    jdouble result;
    result = ((jdouble)n1 + n2) / 2.0;

    return result;
}

static JNINativeMethod method_table[] = {
    /* {"sayhello", "()V", (void *)native_sayhello}, */
    {"average", "(II)D", (void *)native_average},
};

static int registerNativeMethods(JNIEnv *env, const char* className, JNINativeMethod *gMethods, int numMethods)
{
    jclass cls;
    cls = (*env)->FindClass(env, className);
    if (cls == NULL)
    {
        return JNI_FALSE;
    }

    if ((*env)->RegisterNatives(env, cls, gMethods, numMethods) < 0)
    {
        return JNI_FALSE;
    }

    return JNI_TRUE;
}
static int register_jni_load(JNIEnv *env)
{
    return registerNativeMethods(env, JNI_CLASS, method_table, NELEM(method_table));
}

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env = NULL;
    jint result = -1;

    if ((*vm)->GetEnv(vm, (void**)&env, JNI_VERSION_1_4) != JNI_OK)
    {
        return result;
    }

    register_jni_load(env);

    return JNI_VERSION_1_4;
}