// ===================================================================================================
//   ______               _                  _///_ _           _                   _
//  /   _  \             (_)                |  ___| |         | |                 (_)
//  |  [_|  |__  ___  ___ _  ___  _ __      | |__ | | ___  ___| |_ _ __ ___  _ __  _  ___  _   _  ___
//  |   ___/ _ \| __|| __| |/ _ \| '_ \_____|  __|| |/ _ \/  _|  _| '__/   \| '_ \| |/   \| | | |/ _ \
//  |  |  | ( ) |__ ||__ | | ( ) | | | |____| |__ | |  __/| (_| |_| | | (_) | | | | | (_) | |_| |  __/
//  \__|   \__,_|___||___|_|\___/|_| [_|    \____/|_|\___|\____\__\_|  \___/|_| |_|_|\__  |\__,_|\___|
//                                                                                      | |
//                                                                                      \_|
// ===================================================================================================
//
//  Projet  :       Exemple de code #2 : pilotage PWM de moteurs via ESP32-S3-DevKitC + module TB6612FNG
//  Fichier :       prg2-ESP32S3-ModuleTB6612FNG-pilotage-moteurs-avec-librairie.ino
//  Auteur  :       Jérôme TOMSKI
//  Créé le :       27.03.2026
//  Site    :       https://passionelectronique.fr/
//  GitHub  :       https://github.com/PassionElectronique/
//  Licence :       https://creativecommons.org/licenses/by-nc-nd/4.0/deed.fr (BY-NC-ND 4.0 CC)
//
// ===================================================================================================
//
//  Remarques :
//    1)  La librairie "TB6612" de chez SparkFun qu'on va utiliser ici, n'est pas téléchargeable depuis le
//        "gestionnaire de bibliothèques" d'Arduino IDE. Il faudra donc l'installer manuellement ! Voici comment procéder :
//            - Allez sur la page GitHub de la librairie : https://github.com/sparkfun/SparkFun_TB6612FNG_Arduino_Library
//            - Sur la page GitHub, cliquez sur le bouton "Code" puis "Download ZIP", pour télécharger le fichier zip
//            - Une fois fait, allez sur Arduino IDE
//            - Sur Arduino IDE, cliquez dans le menu Sketch (croquis) → Include library (inclure une bibliothèque) → Add .ZIP library (ajouter la bibliothèque .ZIP)
//            - Sélectionnez votre fichier précédemment téléchargé (il doit s'appeller "SparkFun_TB6612FNG_Arduino_Library-master.zip", normalement)
//            - Et effacez le fichier précédemment téléchargé (car il ne sert plus à rien, du fait que Arduino IDE en a fait une copie, dans votre répertoire de librairies arduino !)
//    2)  Les broches ESP32 utilisées ici peuvent être changées, du moment où on n'empiète pas sur les broches "réservées" (USB, UART, BOOT, etc)
//
// ===================================================================================================

// Inclusion de la librairie dont nous aurons besoin ici
#include <SparkFun_TB6612.h>

// Affectation des broches ESP32-S3, pour le pilotage du TB 6612 FNG
#define pin_PWMA  5    // La broche PWMA du module TB6612FNG sera reliée à la broche GPIO5  de l'ESP32-S3-DevKitC
#define pin_AIN2  6    // La broche AIN2 du module TB6612FNG sera reliée à la broche GPIO6  de l'ESP32-S3-DevKitC
#define pin_AIN1  7    // La broche AIN1 du module TB6612FNG sera reliée à la broche GPIO7  de l'ESP32-S3-DevKitC
#define pin_STBY  8    // La broche STBY du module TB6612FNG sera reliée à la broche GPIO8  de l'ESP32-S3-DevKitC
#define pin_BIN1  9    // La broche BIN1 du module TB6612FNG sera reliée à la broche GPIO9  de l'ESP32-S3-DevKitC
#define pin_BIN2 10    // La broche BIN2 du module TB6612FNG sera reliée à la broche GPIO10 de l'ESP32-S3-DevKitC
#define pin_PWMB 11    // La broche PWMB du module TB6612FNG sera reliée à la broche GPIO11 de l'ESP32-S3-DevKitC

// Autres constantes
#define sens_de_rotation_normal_par_defaut    1
#define sens_de_rotation_inverse_par_defaut   -1

// Instanciation d'objets
Motor moteurA = Motor(pin_AIN1, pin_AIN2, pin_PWMA, sens_de_rotation_normal_par_defaut, pin_STBY);
Motor moteurB = Motor(pin_BIN1, pin_BIN2, pin_PWMB, sens_de_rotation_normal_par_defaut, pin_STBY);


// ========================
// Initialisation programme
// ========================
void setup() {

  // Petit délai avant de passer à la boucle loop !
  delay(1000);

}


// =================
// Boucle principale
// =================
void loop() {

  // --------------------------------------------
  // Fonctions utiles (librairie SparkFun_TB6612)
  // --------------------------------------------
  //
  //    moteur.drive(valeur)        → cela permet de fixer la vitesse du moteur, selon la "valeur" donnée (entre -255 et +255)
  //                                  - pour une "marche avant", la valeur doit être comprise entre 0 et 255 inclus (0 = "point mort" ; +255 = "marche avant à fond")
  //                                  - pour une "marche arrière", la valeur doit être comprise entre -255 et 0 inclus (-255 = "marche arrière à fond" ; 0 = "point mort")
  //
  //    moteur.drive(valeur, temps) → idem, mais fait tourner le moteur un temps donné, puis l'arrête
  //
  //    moteur.brake()              → permet d'arrêter le moteur (freinage fort / bobines courts-circuitées)
  //
  //    moteur.standby()            → permet de mettre en sommeil le module TB6612FNG (passage de la broche "STBY" à l'état bas, donc)
  //                                    (nota : pour sortir du "mode sommeil", il suffira tout simplement de faire appel à la fonction "drive" !)


  // ---------------------------------------------------------
  // Test partie 1/4 : rotation du moteur A, en "marche avant"
  // ---------------------------------------------------------
  // Démarrage progressif (de 0 à 100%) de la vitesse
  for(int i = 0; i <= 255; i++) {
    moteurA.drive(i);
    delay(5);
  }
  // Maintien pleine vitesse pendant 2 secondes
  delay(2000);
  // Freinage fort
  moteurA.brake();

  // ---------------------------------------------------------
  // Test partie 1/4 : rotation du moteur B, en "marche avant"
  // ---------------------------------------------------------
  // Démarrage progressif (de 0 à 100%) de la vitesse
  for(int i = 0; i <= 255; i++) {
    moteurB.drive(i);
    delay(5);
  }
  // Maintien pleine vitesse pendant 2 secondes
  delay(2000);
  // Freinage fort
  moteurB.brake();

  // -----------------------------------------------------------
  // Test partie 3/4 : rotation du moteur A, en "marche arrière"
  // -----------------------------------------------------------
  // Démarrage progressif (de 0 à 100%) de la vitesse
  for(int i = 0; i >= -255; i--) {
    moteurA.drive(i);
    delay(5);
  }
  // Maintien pleine vitesse pendant 2 secondes
  delay(2000);
  // Freinage fort
  moteurA.brake();

  // -----------------------------------------------------------
  // Test partie 4/4 : rotation du moteur B, en "marche arrière"
  // -----------------------------------------------------------
  // Démarrage progressif (de 0 à 100%) de la vitesse
  for(int i = 0; i >= -255; i--) {
    moteurB.drive(i);
    delay(5);
  }
  // Maintien pleine vitesse pendant 2 secondes
  delay(2000);
  // Freinage fort
  moteurB.brake();

}
