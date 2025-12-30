# Capteur d'Empreinte Digitale UART pour ESP32

Projet Arduino/ESP32 pour contrôler un capteur d'empreinte digitale UART (Waveshare) en utilisant l'UART matériel Serial2 de l'ESP32.

## 📋 Description

Ce projet est une adaptation du code original Waveshare pour le capteur d'empreinte digitale capacitif UART, optimisé spécifiquement pour l'ESP32. Il utilise l'UART matériel Serial2 au lieu de SoftwareSerial pour une meilleure performance et fiabilité.

### Fonctionnalités

- ✅ Ajout d'empreintes digitales (CMD2)
- ✅ Vérification/Comparaison d'empreintes (CMD3)
- ✅ Suppression d'empreintes (CMD4)
- ✅ Comptage des empreintes enregistrées (CMD1)
- ✅ Mode veille avec réveil automatique (CMD5/CMD6)
- ✅ Communication UART matériel (Serial2)
- ✅ Compatible ESP32 uniquement

## 🔧 Matériel Requis

- **ESP32** (n'importe quel modèle)
- **Capteur d'empreinte digitale UART Waveshare** (modèle D)
- Câbles de connexion
- Alimentation 3.3V pour le capteur

## 📦 Installation

1. Ouvrez le projet dans l'IDE Arduino :
   - Ouvrez `UART_Fingerprint_Sensor_Ar/UART_Fingerprint_Sensor_Ar.ino`

2. Installez le support ESP32 dans l'IDE Arduino si ce n'est pas déjà fait :
   - Ajoutez l'URL du gestionnaire de cartes ESP32 dans les préférences
   - Installez "esp32 by Espressif Systems" via le gestionnaire de cartes

3. Sélectionnez votre carte ESP32 dans l'IDE Arduino

4. Téléversez le code sur votre ESP32

## 🔌 Branchement

### Configuration des Pins

| Signal | Pin ESP32 | Description |
|--------|-----------|-------------|
| **VCC** | 3.3V | Alimentation du capteur (⚠️ 3.3V uniquement) |
| **GND** | GND | Masse commune |
| **RX** | GPIO 16 | Réception des données (Serial2 RX) |
| **TX** | GPIO 17 | Transmission des données (Serial2 TX) |
| **RST** | GPIO 4 | Pin de réinitialisation |
| **WAKE** | GPIO 5 | Pin de réveil (détection tactile) |

### Schéma de Branchement

```
Capteur d'Empreinte Digitale          ESP32
─────────────────────────────         ──────
VCC  ──────────────────────────────── 3.3V
GND  ────────────────────────────────  GND
RX   ────────────────────────────────  GPIO 17 (TX Serial2)
TX   ────────────────────────────────  GPIO 16 (RX Serial2)
RST  ────────────────────────────────  GPIO 4
WAKE ────────────────────────────────  GPIO 5
```

### ⚠️ Notes Importantes

- **Tension d'alimentation** : Le capteur doit être alimenté en **3.3V uniquement**. Ne pas utiliser 5V !
- **Communication UART** : 
  - Baud rate : 19200
  - Utilise Serial2 (UART2 matériel) de l'ESP32
  - RX du capteur → TX de l'ESP32 (GPIO 17)
  - TX du capteur → RX de l'ESP32 (GPIO 16)

## 🚀 Utilisation

### Configuration du Moniteur Série

1. Ouvrez le moniteur série dans l'IDE Arduino
2. Configurez le baud rate à **115200**
3. Redémarrez l'ESP32

### Commandes Disponibles

Envoyez les commandes suivantes via le moniteur série :

| Commande | Description |
|----------|-------------|
| **CMD1** | Affiche le nombre d'empreintes enregistrées |
| **CMD2** | Ajoute une nouvelle empreinte (nécessite 3 scans) |
| **CMD3** | Vérifie/Compare une empreinte avec la base de données |
| **CMD4** | Supprime toutes les empreintes |
| **CMD5** | Active le mode veille (réveil automatique activé) |
| **CMD6** | Réveille le module du mode veille |

### Exemple d'Utilisation

1. **Vérifier le nombre d'empreintes** :
   ```
   CMD1
   ```

2. **Ajouter une empreinte** :
   ```
   CMD2
   ```
   Suivez les instructions : placez votre doigt 3 fois sur le capteur

3. **Vérifier une empreinte** :
   ```
   CMD3
   ```
   Placez votre doigt sur le capteur

## 📁 Structure du Projet

```
ESP32-Fingerprint-Sensor/
├── UART_Fingerprint_Sensor_Ar.ino  # Fichier principal
├── finger.h                         # En-tête avec définitions
├── finger.cpp                       # Implémentation des fonctions
└── README.md                        # Ce fichier

```

## ⚙️ Personnalisation

### Modifier les Pins

Si vous souhaitez utiliser d'autres pins, modifiez les fichiers suivants :

**Dans `finger.h`** :
```cpp
#define  Finger_RST_Pin     4    // Changez pour votre pin RST
#define  Finger_WAKE_Pin    5    // Changez pour votre pin WAKE
```

**Dans `finger.cpp`** :
```cpp
#define FINGER_UART_RX_PIN  16  // Changez pour votre pin RX
#define FINGER_UART_TX_PIN  17  // Changez pour votre pin TX
```

### Pins à Éviter sur ESP32

- **GPIO 0** : Pin BOOT (peut mettre l'ESP32 en mode bootloader)
- **GPIO 1** : TX0 (Serial)
- **GPIO 3** : RX0 (Serial)
- **GPIO 6-11** : Réservés pour la flash (sur certaines cartes)
- **GPIO 34-39** : Entrées uniquement (pas de pull-up interne)

## 🐛 Dépannage

### Pas de communication avec le capteur

- Vérifiez les connexions RX/TX (inversées : RX capteur → TX ESP32)
- Vérifiez que l'alimentation est bien en 3.3V
- Vérifiez le baud rate (19200)
- Vérifiez que Serial2 est bien initialisé

### Erreurs de compilation

- Assurez-vous d'avoir installé le support ESP32 dans l'IDE Arduino
- Vérifiez que tous les fichiers sont dans le même dossier

## 📝 Licence

Code original fourni par Waveshare Team.  
Adaptation pour ESP32 par Mike.

Ce code est libre d'utilisation et de modification. La seule exigence est de mentionner le fournisseur original (Waveshare) dans vos codes.

## 👤 Auteur

- **Mike** - Adaptation pour ESP32
- **Waveshare Team** - Code original

## 🙏 Remerciements

- Waveshare Team pour le code original
- Communauté ESP32 pour le support

## 📚 Ressources

- [Documentation ESP32](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)
- [Waveshare Fingerprint Sensor](https://www.waveshare.com/wiki/UART_Fingerprint_Sensor_(D))
- [Documentation Waveshare Fingerprint Sensor] (https://files.waveshare.com/upload/4/45/UART_Fingerprint_Sensor_%28C%29_User_Manual_en.pdf).

---

**Version** : 1.0 - ESP32 
**Dernière mise à jour** : 2025
