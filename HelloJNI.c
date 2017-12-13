#include <stdio.h>
#include <jni.h>

#define NELEM(x) (sizeof(x) / sizeof((x)[0]))
/* #define JNI_CLASS "HelloJNI" */
/* #define JNI_CLASS "TestJNIPrimitive" */
/* #define JNI_CLASS "TestJNIString" */
#define JNI_CLASS "TestJNIPrimitiveArray"

static void native_sayhello(JNIEnv *env, jclass cls, jstring inJNIString)
{
    const char *inCStr = (*env)->GetStringUTFChars(env, inJNIString, NULL);
    if (NULL == inCStr) return NULL;

    printf("In C, the received string is :%s\n", inCStr);
    (*env)->ReleaseStringUTFChars(env, inJNIString, inCStr);

    char *outCStr = "Hello Java";
    return (*env)->NewStringUTF(env, outCStr);
}

static jdouble native_average(JNIEnv *env ,jobject obj, jint n1, jint n2)
{
    jdouble result;
    result = ((jdouble)n1 + n2) / 2.0;

    return result;
}

static jdoubleArray native_sumAndAverage(JNIEnv *env, jobject obj, jintArray inJNIArray)
{
    jint *inCArray = (*env)->GetIntArrayElements(env, inJNIArray, NULL);
    if (NULL == inCArray) return NULL;
    jsize length = (*env)->GetArrayLength(env, inJNIArray);

    jint sum = 0;
    jint i;
    for (i = 0; i < length; ++i) {
        sum += inCArray[i];
    }

    jdouble average = (jdouble)sum / length;

    (*env)->ReleaseIntArrayElements(env, inJNIArray, inCArray, 0);

    jdouble outCarry[] = {sum, average};
    jdoubleArray outJniArray = (*env)->NewDoubleArray(env, 2);
    if (NULL == outJniArray) return NULL;
    (*env)->SetDoubleArrayRegion(env, outJniArray, 0, 2, outCarry);
    return outJniArray;

}
static JNINativeMethod method_table[] = {
    /* {"sayhello", "()V", (void *)native_sayhello}, */
    /* {"average", "(II)D", (void *)native_average}, */
    /* {"sayhello", "(Ljava/lang/String;)Ljava/lang/String;", (void *)native_sayhello}, */
    {"sumAndAverage", "([I)[D", (void *)native_sumAndAverage},
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