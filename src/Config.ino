#include <Arduino.h>
#include <Preferences.h>
#include "i18n.h"

// Persistente Konfiguration (RAM-Kopie der NVS-Werte).
// Defaults werden verwendet, wenn noch nichts im Flash gespeichert wurde.
double configLatitude       = 51.0;
double configLongitude      =  9.0;
// Default: OPTION_DARKEN_UNLIT (1) | OPTION_USE_LIBRATION (8) = 9
int    configDisplayOptions = 9;
int    configLanguage       = LANG_DE;

static Preferences prefs;
static constexpr const char* PREFS_NAMESPACE = "moon-cfg";

void loadConfig() {
    prefs.begin(PREFS_NAMESPACE, true);
    configLatitude       = prefs.getDouble("lat",  configLatitude);
    configLongitude      = prefs.getDouble("lon",  configLongitude);
    configDisplayOptions = prefs.getInt   ("opts", configDisplayOptions);
    configLanguage       = prefs.getInt   ("lang", configLanguage);
    prefs.end();
    if (configLanguage != LANG_DE && configLanguage != LANG_EN_US) {
        configLanguage = LANG_DE;
    }
    setLanguage((Language) configLanguage);
}

void saveConfig() {
    prefs.begin(PREFS_NAMESPACE, false);
    prefs.putDouble("lat",  configLatitude);
    prefs.putDouble("lon",  configLongitude);
    prefs.putInt   ("opts", configDisplayOptions);
    prefs.putInt   ("lang", configLanguage);
    prefs.end();
}
