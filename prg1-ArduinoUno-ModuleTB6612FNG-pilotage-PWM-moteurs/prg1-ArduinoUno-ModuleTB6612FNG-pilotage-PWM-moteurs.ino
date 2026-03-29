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
//  Projet  :       Exemple de code #1 : pilotage PWM de moteurs via Arduino Uno + module TB6612FNG
//  Fichier :       prg1-ArduinoUno-ModuleTB6612FNG-pilotage-PWM-moteurs.ino
//  Auteur  :       Jérôme TOMSKI
//  Créé le :       20.03.2026
//  Site    :       https://passionelectronique.fr/
//  GitHub  :       https://github.com/PassionElectronique/
//  Licence :       https://creativecommons.org/licenses/by-nc-nd/4.0/deed.fr (BY-NC-ND 4.0 CC)
//
// ===================================================================================================
//
//  Remarques :
//    1)  Pas d'utilisation de librairie spécifique ici, afin de montrer comment piloter "manuellement" des moteurs en PWM, via le TB6612FNG
//    2)  Les broches arduino utilisées ici peuvent être changées, du moment où on garde bien des "vraies sorties PWM" pour piloter les lignes PWMA et PWMB du TB6612FNG
//
// ===================================================================================================

// Affectation des broches Arduino Uno, pour le pilotage du TB 6612 FNG
#define pin_PWMA  5    // La broche PWMA du module TB6612FNG sera reliée à la broche D5  de l'Arduino Uno (ligne PWM native/matérielle Arduino ? Oui !)
#define pin_AIN2  6    // La broche AIN2 du module TB6612FNG sera reliée à la broche D6  de l'Arduino Uno
#define pin_AIN1  7    // La broche AIN1 du module TB6612FNG sera reliée à la broche D7  de l'Arduino Uno
#define pin_STBY  8    // La broche STBY du module TB6612FNG sera reliée à la broche D8  de l'Arduino Uno
#define pin_BIN1  9    // La broche BIN1 du module TB6612FNG sera reliée à la broche D9  de l'Arduino Uno
#define pin_BIN2 10    // La broche BIN2 du module TB6612FNG sera reliée à la broche D10 de l'Arduino Uno
#define pin_PWMB 11    // La broche PWMB du module TB6612FNG sera reliée à la broche D11 de l'Arduino Uno (ligne PWM native/matérielle Arduino ? Oui !)


// ========================
// Initialisation programme
// ========================
void setup() {

  delay(1000);
  // ----------------------------------------------------------------------------
  // Configuration de toutes les broches Arduino en "sortie" et mise à "état bas"
  // ----------------------------------------------------------------------------
  pinMode(pin_STBY, OUTPUT);    digitalWrite(pin_STBY, LOW);
  pinMode(pin_AIN1, OUTPUT);    digitalWrite(pin_AIN1, LOW);
  pinMode(pin_AIN2, OUTPUT);    digitalWrite(pin_AIN2, LOW);
  pinMode(pin_BIN1, OUTPUT);    digitalWrite(pin_BIN1, LOW);
  pinMode(pin_BIN2, OUTPUT);    digitalWrite(pin_BIN2, LOW);
  pinMode(pin_PWMA, OUTPUT);    digitalWrite(pin_PWMA, LOW);
  pinMode(pin_PWMB, OUTPUT);    digitalWrite(pin_PWMB, LOW);

  // -----------------------
  // Activation du TB6612FNG
  // -----------------------
  digitalWrite(pin_STBY, HIGH);     // Mise à "l'état haut" de la ligne STBY, pour activer la puce TB6612 FNG

}


// =================
// Boucle principale
// =================
void loop() {

  // ----------------
  // Principe de base
  // ----------------
  // Pour faire passer la vitesse d'un moteur de 0 à 100%, on va simplement utiliser un signal PWM,
  // et faire varier son rapport cyclique de 0 à 100%. Pour ce faire, on utilisera la fonction
  // "analogWrite", sur une sortie spécifique PWM arduino ; à noter que cette fonction requiert
  // un argument compris entre 0 et 255 (0 correspondant à un rapport cyclique de 0%, et 255 à un
  // rapport cyclique de 100%). Juste pour info : le signal PWM aura une fréquence fixe (celle par défaut),
  // donc seul son rapport cyclique varie (faisant ainsi varier la tension moyenne, aux bornes des moteurs).


  // -----------------------------------------------------------|
  // |            Table de vérité pilotage moteurs              |
  // -----------------------------------------------------------|
  // | xIN1 | xIN2 | Mode                                       |
  // |----------------------------------------------------------|
  // | LOW  | LOW  | Arrêt            (rotation libre)          |
  // | LOW  | HIGH | Marche "arrière" (rotation sens "inverse") |
  // | HIGH | LOW  | Marche "avant"   (rotation sens "normal")  |
  // | HIGH | HIGH | Arrêt            (rotation freinée)        |
  // -----------------------------------------------------------|


  // -----------------------------------------------------------------------------------------------
  // Test partie 1/4 : passage progressif (de 0 à 100%) de la vitesse du moteur A, en "marche avant"
  // -----------------------------------------------------------------------------------------------
  digitalWrite(pin_AIN1, HIGH);     // MARCHE AVANT   (IN1 à l'état haut, et IN2 à l'état bas)
  digitalWrite(pin_AIN2, LOW);
  for(int i=0 ; i <= 255 ; i++) {
    analogWrite(pin_PWMA, i);
    delay(5);
  }
  delay(2000);                      // Laisser tourner "à fond" pendant 2 secondes de plus
  digitalWrite(pin_AIN1, HIGH);     // ARRÊT          (IN1 et IN2 à l'état haut)
  digitalWrite(pin_AIN2, HIGH);

  // -----------------------------------------------------------------------------------------------
  // Test partie 2/4 : passage progressif (de 0 à 100%) de la vitesse du moteur B, en "marche avant"
  // -----------------------------------------------------------------------------------------------
  digitalWrite(pin_BIN1, HIGH);     // MARCHE AVANT   (IN1 à l'état haut, et IN2 à l'état bas)
  digitalWrite(pin_BIN2, LOW);
  for(int i=0 ; i <= 255 ; i++) {
    analogWrite(pin_PWMB, i);
    delay(5);
  }
  delay(2000);                      // Laisser tourner "à fond" pendant 2 secondes de plus
  digitalWrite(pin_BIN1, HIGH);     // ARRÊT          (IN1 et IN2 à l'état haut)
  digitalWrite(pin_BIN2, HIGH);

  // -------------------------------------------------------------------------------------------------
  // Test partie 3/4 : passage progressif (de 0 à 100%) de la vitesse du moteur A, en "marche arrière"
  // -------------------------------------------------------------------------------------------------
  digitalWrite(pin_AIN1, LOW);      // MARCHE ARRIÈRE (IN1 à l'état bas, et IN2 à l'état haut)
  digitalWrite(pin_AIN2, HIGH);
  for(int i=0 ; i <= 255 ; i++) {
    analogWrite(pin_PWMA, i);
    delay(5);
  }
  delay(2000);                      // Laisser tourner "à fond" pendant 2 secondes de plus
  digitalWrite(pin_AIN1, HIGH);     // ARRÊT          (IN1 et IN2 à l'état haut)
  digitalWrite(pin_AIN2, HIGH);

  // -------------------------------------------------------------------------------------------------
  // Test partie 4/4 : passage progressif (de 0 à 100%) de la vitesse du moteur B, en "marche arrière"
  // -------------------------------------------------------------------------------------------------
  digitalWrite(pin_BIN1, LOW);      // MARCHE ARRIÈRE (IN1 à l'état bas, et IN2 à l'état haut)
  digitalWrite(pin_BIN2, HIGH);
  for(int i=0 ; i <= 255 ; i++) {
    analogWrite(pin_PWMB, i);
    delay(5);
  }
  delay(2000);                      // Laisser tourner "à fond" pendant 2 secondes de plus
  digitalWrite(pin_BIN1, HIGH);     // ARRÊT          (IN1 et IN2 à l'état haut)
  digitalWrite(pin_BIN2, HIGH);

}
