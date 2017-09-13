#include <CoreFoundation/CoreFoundation.h>
#include <objc/objc.h>
#include <objc/objc-runtime.h>
#include <iostream>

void _showOutput(char* outputLabel, char* outputString) asm("_showOutput");
void _showOutput(char* outputLabel, char* outputString){
	const void* keys[] = {
		kCFUserNotificationAlertHeaderKey,
		kCFUserNotificationAlertMessageKey,
		kCFUserNotificationDefaultButtonTitleKey
	};
	const void* values[] = {
		CFStringCreateWithCString(NULL, outputLabel, kCFStringEncodingUTF8),
		CFStringCreateWithCString(NULL, outputString, kCFStringEncodingUTF8),
		CFSTR("OK")
	};
	CFUserNotificationRef userNotification = CFUserNotificationCreate(
		NULL, //Default Allocater
		0, //No timeout
		kCFUserNotificationPlainAlertLevel, //Normal alert
		NULL, //We don't need the response
		CFDictionaryCreate(0, keys, values, sizeof(keys)/sizeof(*keys), &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks)
	);
	CFUserNotificationReceiveResponse(userNotification, 0, NULL);
}
void _getInput(char* inputPrompt, char* result, int maxChars) asm("_getInput");
void _getInput(char* inputPrompt, char* result, int maxChars){
	const void* keys[] = {
		kCFUserNotificationAlertHeaderKey,
		kCFUserNotificationTextFieldTitlesKey,
		kCFUserNotificationDefaultButtonTitleKey
	};
	const void* values[] = {
		CFStringCreateWithCString(NULL, inputPrompt, kCFStringEncodingUTF8),
		CFSTR(""),
		CFSTR("OK")
	};
	CFUserNotificationRef userNotification = CFUserNotificationCreate(
		NULL, //Default Allocater
		0, //No timeout
		kCFUserNotificationPlainAlertLevel, //Normal alert
		NULL, //We don't need the response
		CFDictionaryCreate(0, keys, values, sizeof(keys)/sizeof(*keys), &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks)
	);
	CFUserNotificationReceiveResponse(userNotification, 0, NULL);
	CFStringRef resultString = CFUserNotificationGetResponseValue(userNotification, kCFUserNotificationTextFieldValuesKey, 0);
	CFStringGetCString(resultString, result, maxChars, kCFStringEncodingUTF8);

}
int _MainProc(void) asm ("_MainProc");
int main(int argc, char** argv)
{
    id app = NULL;
    id pool = (id)objc_getClass("NSAutoreleasePool");
    if (!pool)
    {
        std::cerr << "Unable to get NSAutoreleasePool!\nAborting\n";
        return -1;
    }
    pool = objc_msgSend(pool, sel_registerName("alloc"));
    if (!pool)
    {
        std::cerr << "Unable to create NSAutoreleasePool...\nAborting...\n";
        return -1;
    }
    pool = objc_msgSend(pool, sel_registerName("init"));

    app = objc_msgSend((id)objc_getClass("NSApplication"),
                       sel_registerName("sharedApplication"));

    int result = _MainProc();

    objc_msgSend(pool, sel_registerName("release"));
    return result;
}
