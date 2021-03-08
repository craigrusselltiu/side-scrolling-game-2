#include <QFile>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFileInfo>
#include "config.h"

// Constructors + Destructors
Config::Config(){}
Config::Config(std::string file){
    loadFile(file);
}
Config::~Config(){}

// Load config file
bool Config::loadFile(std::string filename){

    // Init to invalid
    valid = false;

    // Read JSON file
    QString content;
    QFile file;
    file.setFileName(QString(filename.c_str()));
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!file.exists()) return fileNotFoundError("config.json");
    content = file.readAll();
    file.close();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(content.toUtf8());
    if(jsonDoc.isNull()){
        errorMsg = "Invalid JSON format";
        return false;
    }
    QJsonObject json = jsonDoc.object();

    // Load size and verify valid option
    if(json.contains("size")){
        size = json.value("size").toString().toStdString();
        if(size != "tiny" && size != "normal" && size != "large" && size != "giant") {
            errorMsg = "Invalid size value";
            return false;
        }
    }
    else return paramNotFoundError("size");

    // Load stage number
    if(json.contains("stage")){
        stage = json.value("stage").toInt();
    }

    // Load other options
    if(json.contains("initX"))
        initX = json.value("initX").toInt();
    else return paramNotFoundError("initX");
    if(json.contains("initY"))
        initY = json.value("initY").toInt();
    else return paramNotFoundError("initY");
    if(json.contains("velocity"))
        velocity = json.value("velocity").toInt();
    else return paramNotFoundError("velocity");
    if(json.contains("airCandyPosition"))
        airPos = json.value("airCandyPosition").toInt();
    else return paramNotFoundError("airCandyPosition");
    if(json.contains("groundCandyPosition"))
        groundPos = json.value("groundCandyPosition").toInt();
    else return paramNotFoundError("groundCandyPosition");

    if(stage >= 2) {

        // Load alternate textures
        if(json.contains("backgroundTextureAlt"))
            backgroundTexture = json.value("backgroundTextureAlt").toString().toStdString();
        else return paramNotFoundError("backgroundTextureAlt");
        if(json.contains("playerTextureAlt"))
            playerTexture = json.value("playerTextureAlt").toString().toStdString();
        else return paramNotFoundError("playerTextureAlt");
        if(json.contains("pauseTextureAlt"))
            pauseTexture = json.value("pauseTextureAlt").toString().toStdString();
        else return paramNotFoundError("pauseTextureAlt");
        if(json.contains("airCandyAlt")){
            QJsonArray values = json.value("airCandyAlt").toArray();
            for(int i = 0; i < values.count(); i++)
                airCandyTextures.push_back(values.at(i).toString().toStdString());
        }
        else return paramNotFoundError("airCandyAlt");
        if(json.contains("groundCandyAlt")){
            QJsonArray values = json.value("groundCandyAlt").toArray();
            for(int i = 0; i < values.count(); i++)
                groundCandyTextures.push_back(values.at(i).toString().toStdString());
        }
        else return paramNotFoundError("groundCandyAlt");
    }
    else{

        // Load textures
        if(json.contains("backgroundTexture"))
            backgroundTexture = json.value("backgroundTexture").toString().toStdString();
        else return paramNotFoundError("backgroundTexture");
        if(json.contains("playerTexture"))
            playerTexture = json.value("playerTexture").toString().toStdString();
        else return paramNotFoundError("playerTexture");
        if(json.contains("pauseTexture"))
            pauseTexture = json.value("pauseTexture").toString().toStdString();
        else return paramNotFoundError("pauseTexture");
        if(json.contains("airCandyTextures")){
            QJsonArray values = json.value("airCandyTextures").toArray();
            for(int i = 0; i < values.count(); i++)
                airCandyTextures.push_back(values.at(i).toString().toStdString());
        }
        else return paramNotFoundError("airCandyTextures");
        if(json.contains("groundCandyTextures")){
            QJsonArray values = json.value("groundCandyTextures").toArray();
            for(int i = 0; i < values.count(); i++)
                groundCandyTextures.push_back(values.at(i).toString().toStdString());
        }
        else return paramNotFoundError("groundCandyTextures");
    }

    // Check textures exist
    if(!fileExists(backgroundTexture)) return fileNotFoundError(backgroundTexture);
    if(!fileExists(playerTexture)) return fileNotFoundError(playerTexture);
    if(!fileExists(pauseTexture)) return fileNotFoundError(pauseTexture);
    for(unsigned int i = 0; i < airCandyTextures.size(); i++)
        if(!fileExists(airCandyTextures[i])) return fileNotFoundError(airCandyTextures[i]);
    for(unsigned int i = 0; i < groundCandyTextures.size(); i++)
        if(!fileExists(groundCandyTextures[i])) return fileNotFoundError(groundCandyTextures[i]);

    // Load stage 2 configurations
    if(stage >= 2){
        if(json.contains("obstacleSizeX"))
            obstacleSizeX = json.value("obstacleSizeX").toInt();
        else return paramNotFoundError("obstacleSizeX");
        if(json.contains("obstacleSizeY"))
            obstacleSizeY = json.value("obstacleSizeY").toInt();
        else return paramNotFoundError("obstacleSizeY");
        if(json.contains("obstacleDistance"))
            obstacleDistance = json.value("obstacleDistance").toInt();
        else return paramNotFoundError("obstacleDistance");
        if(json.contains("obstacleTextures")){
            QJsonArray values = json.value("obstacleTextures").toArray();
            for(int i = 0; i < values.count(); i++)
                obstacleTextures.push_back(values.at(i).toString().toStdString());
        }
        else return paramNotFoundError("obstacleSequence");
        if(json.contains("obstacleSequence")){
            QJsonArray values = json.value("obstacleSequence").toArray();
            for(int i = 0; i < values.count(); i++)
                obstacleSequence.push_back(values.at(i).toInt());
        }
        else return paramNotFoundError("obstacleSequence");
        if(json.contains("gravity"))
            gravity = json.value("gravity").toInt();
        else return paramNotFoundError("gravity");
        if(json.contains("jumpVelocity"))
            jumpVelocity = json.value("jumpVelocity").toInt();
        else return paramNotFoundError("jumpVelocity");
        if(json.contains("gameOverTexture"))
            gameOverTexture = json.value("gameOverTexture").toString().toStdString();
        else return paramNotFoundError("gameOverTexture");
        if(json.contains("auraTexture"))
            auraTexture = json.value("auraTexture").toString().toStdString();
        else return paramNotFoundError("auraTexture");
        if(json.contains("moveTexture"))
            moveTexture = json.value("moveTexture").toString().toStdString();
        else return paramNotFoundError("moveTexture");
        if(json.contains("obstacleVelocity"))
            obstacleVelocity = json.value("obstacleVelocity").toInt();
        else return paramNotFoundError("obstacleVelocity");
        if(json.contains("obstacleEdgeDistance"))
            obstacleEdgeDistance = json.value("obstacleEdgeDistance").toInt();
        else return paramNotFoundError("obstacleEdgeDistance");

        // Read test mode and initialise
        if(json.contains("testMode"))
            testMode = json.value("testMode").toBool();
        else return paramNotFoundError("testMode");

        if(testMode){
            initX = 100;
            initY = 100;
            obstacleSizeX = 100;
            obstacleSizeY = 100;
            obstacleDistance = 500;
            velocity = 4;

            playerTexture = "resources/textures/testPlayer.png";
            gameOverTexture = "resources/textures/testComplete.png";
            backgroundTexture = "resources/textures/testStage.png";
            airCandyTextures.clear();
            groundCandyTextures.clear();
            obstacleTextures.clear();
            obstacleTextures.push_back("resources/textures/testObstacle.png");
            obstacleSequence.clear();
            obstacleSequence.push_back(300);
            obstacleSequence.push_back(241);
            obstacleSequence.push_back(100);
        }

        // Check for invalid parameters
        if(obstacleSizeX<=0) return invalidParam("obstacleSizeX");
        if(obstacleSizeY<=0) return invalidParam("obstacleSizeY");
        if(obstacleDistance<0) return invalidParam("obstacleDistance");
        if(gravity>0) return invalidParam("gravity");
        if(jumpVelocity<0) return invalidParam("jumpVelocity");
    }

    // Everything successfully parsed so set valid
    valid = true;
    return valid;

}

// Helper functions
bool Config::fileExists(std::string path){
    return QFileInfo::exists(path.c_str()) && QFileInfo(path.c_str()).isFile();
}
bool Config::fileNotFoundError(std::string file){
    errorMsg = "File not found: " + file;
    return false;
}
bool Config::paramNotFoundError(std::string param){
    errorMsg = "Parameter not found: " + param;
    return false;
}
bool Config::invalidParam(std::string param){
    errorMsg = "Invalid parameter: " + param;
    return false;
}

// Getters
bool Config::isValid(){return valid;}
std::string Config::getErrorMsg(){return errorMsg;}
std::string Config::getSize(){return size;}
int Config::getInitX(){return initX;}
int Config::getInitY(){return initY;}
int Config::getVelocity(){return velocity;}
std::string Config::getBackgroundTexture(){return backgroundTexture;}
std::string Config::getPlayerTexture(){return playerTexture;}
std::string Config::getPauseTexture(){return pauseTexture;}
std::vector<std::string> Config::getAirCandyTextures(){return airCandyTextures;}
std::vector<std::string> Config::getGroundCandyTextures(){return groundCandyTextures;}
int Config::getAirPos(){return airPos;}
int Config::getGroundPos(){return groundPos;}

int Config::getStage(){return stage;}
int Config::getObstacleSizeX(){return obstacleSizeX;}
int Config::getObstacleSizeY(){return obstacleSizeY;}
int Config::getObstacleDistance(){return obstacleDistance;}
std::vector<std::string> Config::getObstacleTextures(){return obstacleTextures;}
std::vector<int> Config::getObstacleSequence(){return obstacleSequence;}
int Config::getGravity(){return gravity;}
int Config::getJumpVelocity(){return jumpVelocity;}
std::string Config::getGameOverTexture(){return gameOverTexture;}
std::string Config::getAuraTexture(){return auraTexture;}
std::string Config::getMoveTexture(){return moveTexture;}
int Config::getObstacleVelocity(){return obstacleVelocity;}
int Config::getObstacleEdgeDistance(){return obstacleEdgeDistance;}
bool Config::getTestMode(){return testMode;}
