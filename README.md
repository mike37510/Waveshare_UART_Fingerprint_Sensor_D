# Capteur d'Empreinte Digitale UART pour ESP32

Projet Arduino/ESP32 pour contrôler un capteur d'empreinte digitale UART (Waveshare) via une **interface web embarquée** avec connexion WiFi. Utilise l'UART matériel Serial2 de l'ESP32.

## 📋 Description

Ce projet est une adaptation du code original Waveshare pour le capteur d'empreinte digitale capacitif UART, optimisé spécifiquement pour l'ESP32 avec une **interface web moderne**. Il utilise l'UART matériel Serial2 et un serveur web embarqué pour contrôler toutes les fonctionnalités du capteur via un navigateur.

### Fonctionnalités

- 🌐 **Interface Web embarquée** - Contrôle via navigateur web
- 📱 **Design responsive** - Fonctionne sur mobile, tablette et PC
- 👤 **Gestion des noms d'utilisateurs** - Associez un nom à chaque empreinte
- 📋 **Liste des utilisateurs** - Visualisez tous les utilisateurs enregistrés avec leurs noms
- ✅ Ajout d'empreintes digitales (CMD2) avec nom d'utilisateur
- ✅ Vérification/Comparaison d'empreintes (CMD3) avec affichage du nom
- ✅ Suppression d'empreintes (CMD4)
- ✅ Comptage des empreintes enregistrées (CMD1)
- ✅ Mode veille avec réveil automatique (CMD5/CMD6)
- ✅ Communication UART matériel (Serial2)
- ✅ WiFi - Point d'accès ou connexion à un réseau existant
- ✅ Stockage persistant des noms dans l'EEPROM
- ✅ Compatible ESP32 uniquement

## 🔧 Matériel Requis

- **ESP32** (n'importe quel modèle)
- **Capteur d'empreinte digitale UART Waveshare** (modèle D)
- Câbles de connexion
- Alimentation 3.3V pour le capteur
- **Optionnel** : Boîtier imprimé en 3D (fichiers STL fournis dans le dépôt)

## 📦 Installation

1. Ouvrez le projet dans l'IDE Arduino :
   - Ouvrez `UART_Fingerprint_Sensor_Ar/UART_Fingerprint_Sensor_Ar.ino`

2. Installez le support ESP32 dans l'IDE Arduino si ce n'est pas déjà fait :
   - Ajoutez l'URL du gestionnaire de cartes ESP32 dans les préférences
   - Installez "esp32 by Espressif Systems" via le gestionnaire de cartes

3. **Configurez le WiFi** dans le fichier `.ino` :
   - **Option 1 (Recommandé)** : Mode Point d'Accès (AP)
     - L'ESP32 crée son propre réseau WiFi
     - Modifiez `ssid_ap` et `password_ap` si nécessaire
   - **Option 2** : Connexion à un réseau WiFi existant
     - Définissez `WIFI_MODE_AP` à `false`
     - Définissez `WIFI_MODE_STA` à `true`
     - Configurez `ssid_sta` et `password_sta` avec vos identifiants WiFi

4. Sélectionnez votre carte ESP32 dans l'IDE Arduino

5. Téléversez le code sur votre ESP32

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

### Interface Web

1. **Après le téléversement**, ouvrez le moniteur série (115200 bauds) pour voir l'adresse IP

2. **Mode Point d'Accès (AP)** :
   - Connectez-vous au réseau WiFi créé par l'ESP32
   - SSID par défaut : `ESP32-Fingerprint`
   - Mot de passe par défaut : `12345678`
   - Ouvrez votre navigateur et allez à : `http://192.168.4.1`

3. **Mode Station (WiFi existant)** :
   - L'ESP32 se connecte à votre réseau WiFi
   - L'adresse IP s'affiche dans le moniteur série
   - Ouvrez votre navigateur et allez à cette adresse IP

### Interface Web - Commandes Disponibles

L'interface web affiche :
- 📊 **Statut en temps réel** : Nombre d'empreintes, dernier utilisateur (avec nom si disponible), état du système
- 🔘 **Boutons de commande** pour toutes les fonctions :

| Bouton | Commande | Description |
|--------|----------|-------------|
| **CMD1** | Compter empreintes | Affiche le nombre d'empreintes enregistrées |
| **CMD2** | Ajouter empreinte | Ajoute une nouvelle empreinte avec nom d'utilisateur (3 scans requis) |
| **CMD3** | Vérifier empreinte | Compare une empreinte avec la base de données et affiche le nom |
| **📋** | Liste utilisateurs | Affiche tous les utilisateurs enregistrés avec leurs noms et IDs |
| **CMD4** | Effacer toutes | ⚠️ Supprime toutes les empreintes et leurs noms |
| **CMD5** | Mode veille | Active le mode veille avec réveil automatique |
| **CMD6** | Réveiller | Réveille le module du mode veille |

### Utilisation de l'Interface

1. **Vérifier le nombre d'empreintes** :
   - Cliquez sur le bouton **CMD1**
   - Le nombre s'affiche dans la section "État du Système"

2. **Ajouter une empreinte avec nom** :
   - Cliquez sur le bouton **CMD2**
   - Une fenêtre s'ouvre pour saisir le nom de l'utilisateur
   - Entrez le nom et cliquez sur "Confirmer"
   - Placez votre doigt **3 fois** sur le capteur (suivez les instructions du moniteur série)
   - Le nom est sauvegardé automatiquement avec l'ID de l'empreinte
   - Un message de confirmation s'affiche avec le nom et l'ID

3. **Vérifier une empreinte** :
   - Cliquez sur le bouton **CMD3**
   - Placez votre doigt sur le capteur
   - Le résultat s'affiche avec le nom de l'utilisateur (si enregistré) ou l'ID

4. **Voir la liste des utilisateurs** :
   - Cliquez sur le bouton **📋 Liste utilisateurs**
   - Une fenêtre s'ouvre avec tous les utilisateurs enregistrés
   - Chaque utilisateur affiche son nom (ou "Sans nom") et son ID
   - Le total d'utilisateurs est affiché en bas

5. **Effacer toutes les empreintes** :
   - ⚠️ Cliquez sur le bouton **CMD4** (rouge)
   - Toutes les empreintes et leurs noms sont supprimés
   - Confirmation immédiate

6. **Mode veille/Réveil** :
   - **CMD5** : Active le mode veille (réveil automatique par détection tactile)
   - **CMD6** : Réveille le module

### Moniteur Série (Optionnel)

Vous pouvez toujours utiliser le moniteur série pour voir les messages détaillés et les résultats des opérations.

## 🖼️ Photos du Projet

Le dépôt contient des photos du projet montrant :
- L'assemblage final du système
- Le branchement des composants
- L'interface web en action

Consultez les fichiers JPG dans le dépôt pour voir des exemples visuels du projet.

## 🖨️ Fichiers STL pour Impression 3D

Ce projet inclut des **fichiers STL** pour créer un boîtier personnalisé pour votre ESP32 et capteur d'empreinte digitale :

- **ESP1.stl** - Première partie du boîtier
- **ESP2.stl** - Deuxième partie du boîtier

Ces fichiers STL sont prêts à être imprimés en 3D et permettent de créer un boîtier professionnel et sur mesure pour votre projet.

### Instructions d'Impression 3D

1. **Téléchargez les fichiers STL** depuis le dépôt (`ESP1.stl` et `ESP2.stl`)
2. **Importez-les** dans votre logiciel de découpe 3D (Cura, PrusaSlicer, Simplify3D, etc.)
3. **Ajustez les paramètres** selon votre imprimante 3D (matériau, température, remplissage)
4. **Imprimez les deux parties** du boîtier
5. **Assemblez** le boîtier autour de votre ESP32 et du capteur d'empreinte digitale

**Note** : Les fichiers STL sont fournis tels quels. Vous pouvez les modifier selon vos besoins avec un logiciel de modélisation 3D (Blender, Fusion 360, FreeCAD, etc.).

## 📁 Structure du Projet

```
ESP32-Fingerprint-Sensor/
│
├── UART_Fingerprint_Sensor_Ar/
│   ├── UART_Fingerprint_Sensor_Ar.ino  # Fichier principal (serveur web)
│   ├── finger.h                         # En-tête avec définitions
│   ├── finger.cpp                       # Implémentation des fonctions capteur
│   ├── webpage.h                        # Interface HTML embarquée
│   └── user_names.h                     # Gestion des noms d'utilisateurs (EEPROM)
│
├── ESP1.stl                             # Fichier STL pour impression 3D (boîtier partie 1)
├── ESP2.stl                             # Fichier STL pour impression 3D (boîtier partie 2)
├── *.jpg                                # Photos du projet
├── README.md                            # Ce fichier
└── .gitignore                           # Fichiers à ignorer par Git
```

## 🖼️ Photos du Projet

Le dépôt contient des **photos du projet** montrant :
- L'assemblage final du système
- Le branchement des composants (ESP32, capteur, connexions)
- L'interface web en action
- Le boîtier imprimé en 3D (si utilisé)

Consultez les fichiers JPG dans le dépôt pour voir des exemples visuels du projet complet.

## 🖨️ Fichiers STL pour Impression 3D

Ce projet inclut des **fichiers STL** pour créer un boîtier personnalisé pour votre ESP32 et capteur d'empreinte digitale :

- **ESP1.stl** - Première partie du boîtier
- **ESP2.stl** - Deuxième partie du boîtier

Ces fichiers STL sont prêts à être imprimés en 3D et permettent de créer un boîtier professionnel et sur mesure pour votre projet.

### Instructions d'Impression 3D

1. **Téléchargez les fichiers STL** depuis le dépôt (`ESP1.stl` et `ESP2.stl`)
2. **Importez-les** dans votre logiciel de découpe 3D (Cura, PrusaSlicer, Simplify3D, etc.)
3. **Ajustez les paramètres** selon votre imprimante 3D :
   - Matériau recommandé : PLA ou PETG
   - Remplissage : 15-20%
   - Résolution : 0.2mm (standard) ou 0.15mm (haute qualité)
4. **Imprimez les deux parties** du boîtier
5. **Assemblez** le boîtier autour de votre ESP32 et du capteur d'empreinte digitale

**Note** : Les fichiers STL sont fournis tels quels. Vous pouvez les modifier selon vos besoins avec un logiciel de modélisation 3D (Blender, Fusion 360, FreeCAD, etc.) si vous souhaitez adapter les dimensions ou ajouter des fonctionnalités.

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
- [Waveshare Fingerprint Sensor](https://www.waveshare.com/)

---

**Version** : 3.1 - ESP32 Web Interface avec Gestion des Noms  
**Dernière mise à jour** : 2025

## 🆕 Nouvelles Fonctionnalités

### Gestion des Noms d'Utilisateurs

- **Ajout de nom lors de l'enregistrement** : Lors de l'ajout d'une empreinte (CMD2), vous pouvez maintenant associer un nom à l'utilisateur
- **Affichage des noms** : Lors de la vérification (CMD3), le nom de l'utilisateur s'affiche au lieu de seulement l'ID
- **Liste des utilisateurs** : Nouveau bouton pour voir tous les utilisateurs enregistrés avec leurs noms et IDs
- **Stockage persistant** : Les noms sont sauvegardés dans l'EEPROM de l'ESP32 et persistent après redémarrage
- **Statut en temps réel** : Le statut affiche le nom du dernier utilisateur vérifié

### Interface Améliorée

- **Modal de saisie** : Fenêtre popup pour entrer le nom lors de l'ajout
- **Liste interactive** : Fenêtre modale avec défilement pour voir tous les utilisateurs
- **Design cohérent** : Interface moderne et intuitive

## 📦 Contenu du Dépôt

Ce dépôt contient :

- ✅ **Code source complet** - Tous les fichiers nécessaires pour compiler et utiliser le projet
- 🖨️ **Fichiers STL** - Modèles 3D pour imprimer un boîtier personnalisé (ESP1.stl, ESP2.stl)
- 📸 **Photos du projet** - Images montrant l'assemblage et l'utilisation
- 📚 **Documentation complète** - Ce README avec toutes les instructions

## 🔧 Configuration WiFi

### Mode Point d'Accès (AP)

L'ESP32 crée son propre réseau WiFi. Parfait pour un usage autonome.

```cpp
const bool USE_WIFI_AP = true;  // Active le mode AP
const char* ssid_ap = "ESP32-Fingerprint";
const char* password_ap = "12345678";  // Minimum 8 caractères
```

### Mode Station (Connexion à un réseau existant)

Pour connecter l'ESP32 à votre réseau WiFi domestique.

```cpp
const bool USE_WIFI_AP = false;  // Désactive le mode AP
const bool USE_WIFI_STA = true;  // Active le mode Station
const char* ssid_sta = "VOTRE_SSID";
const char* password_sta = "VOTRE_MOT_DE_PASSE";
```

## 📡 API REST

L'interface web utilise une API REST. Vous pouvez également appeler ces endpoints directement :

- `GET /` - Page web principale
- `GET /api/status` - Obtenir le statut (JSON) avec nom du dernier utilisateur
- `GET /api/users` - Obtenir la liste de tous les utilisateurs avec leurs noms (JSON)
- `POST /api/cmd1` - Compter les empreintes
- `POST /api/cmd2` - Ajouter une empreinte (body JSON: `{"name":"Nom utilisateur"}`)
- `POST /api/cmd3` - Vérifier une empreinte
- `POST /api/cmd4` - Effacer toutes les empreintes (et leurs noms)
- `POST /api/cmd5` - Activer le mode veille
- `POST /api/cmd6` - Réveiller le module

### Exemple d'utilisation de l'API

**Ajouter une empreinte avec nom :**
```bash
curl -X POST http://192.168.1.100/api/cmd2 \
  -H "Content-Type: application/json" \
  -d '{"name":"Jean Dupont"}'
```

**Obtenir la liste des utilisateurs :**
```bash
curl http://192.168.1.100/api/users
```

**Réponse JSON :**
```json
{
  "success": true,
  "users": [
    {"id": 1, "name": "Jean Dupont"},
    {"id": 2, "name": "Marie Martin"}
  ],
  "total": 2
}
```
