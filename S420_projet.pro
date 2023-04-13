QT       += quick core gui network serialbus charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    ihm.cpp \
    simulateur.cpp \
    modbus_srv.cpp \
    polaire.cpp \
    qamabstractserver.cpp \
    qammodbusmap.cpp \
    qammodbusdata.cpp \
    qamtcpserver.cpp \
    qamtcpconnection.cpp


HEADERS += \
    ihm.h \
    mydoublespinbox.h \
    mygraphicsview.h \
    myprogressbar.h \
    myspinbox.h \
    simulateur.h \
    modbus_srv.h \
    polaire.h \
    qamabstractserver.h \
    qammodbusmap.h \
    qammodbusdata.h \
    qamtcpserver.h \
    qamtcpconnection.h

FORMS += \
    ihm.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    android/AndroidManifest.xml \
    android/AndroidManifest.xml \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/build.gradle \
    android/build.gradle \
    android/gradle.properties \
    android/gradle.properties \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew \
    android/gradlew \
    android/gradlew.bat \
    android/gradlew.bat \
    android/gradlew.bat \
    android/res/values/libs.xml \
    android/res/values/libs.xml \
    android/res/values/libs.xml \
    s420_uml.qmodel

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

RESOURCES += \
    Class40.pol \
    S420-6-API.csv \
    images/icon_minus.png \
    images/icon_plus.png \
    images/background.png \
    images/Vue_cote_boat.png \
    images/Vue_top_boat.png \
    images/Vue_back_boat.png \
    images/icon_plug_on.png \
    images/icon_plug_off.png \
    images/wind.png \
    images/Bome.png \
    font/RobotoMono.ttf \
    font/Poppins.ttf

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}
