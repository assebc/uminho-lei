#include "../../include/XMLParser/xmlParser.h"

using namespace std;

XMLParser::XMLParser(){
    window_width = 800;
    window_height = 800;
    config_file = "../config/config.xml";
}

XMLParser::XMLParser(char * file) {
    window_width = 800;
    window_height = 800;
    config_file = string(file);
}

XMLParser::XMLParser(string file) {
    window_width = 800;
    window_height = 800;
    config_file = file;
}

Point3D XMLParser::parsePoint(XMLElement* info) {
    const char* readX = info->Attribute("x");
    const char* readY = info->Attribute("y");
    const char* readZ = info->Attribute("z");
    float x = readX ? atof(readX) : 0;
    float y = readY ? atof(readY) : 0;
    float z = readZ ? atof(readZ) : 0;
    return Point3D(x, y, z);
}

Group XMLParser::parseGroup(XMLElement* group) {
    Group g = Group();

    XMLElement* transform = group->FirstChildElement("transform");
    if (transform) {

        XMLElement* rotation = transform->FirstChildElement("rotate");
        if (rotation) {
            shared_ptr<Rotation> t;
            bool type = true;
            const char* readAngle;
            const char* readTime;
            Point3D point = parsePoint(rotation);
            if (readTime = rotation->Attribute("time")) {
                const char* clockwise = rotation->Attribute("clockwise");
                t = make_shared<Rotation>(atof(readTime), string(clockwise).size(), point.x, point.y, point.z);
            }
            else {
                readAngle = rotation->Attribute("angle");
                t = make_shared<Rotation>(atof(readAngle), point.x, point.y, point.z);
            }
            g.addTransform(t);
        }

        XMLElement* translation = transform->FirstChildElement("translate");
        if (translation) {
            shared_ptr<Transform> t;
            if (const char* timeString = translation->Attribute("time")) {
                double time = atof(timeString);
                vector<Point3D> vector_points;
                for (XMLElement* point = translation->FirstChildElement("point");point;point = point->NextSiblingElement()) {
                    vector_points.push_back(parsePoint(point));
                }
                t = make_shared<Translation>(time, vector_points);
            }
            else {
                Point3D point = parsePoint(translation);
                t = make_shared<Translation>(point.x, point.y, point.z);
            }
            g.addTransform(t);
        }

        XMLElement* scale = transform->FirstChildElement("scale");
        if (scale) {
            Point3D point = parsePoint(scale);
            shared_ptr<Scale> t = make_shared<Scale>(point.x, point.y, point.z);
            g.addTransform(t);
        }

    }

    XMLElement* pModels = group->FirstChildElement("models");
    if (pModels) {
        XMLElement* pModel;
        for (pModel = pModels->FirstChildElement(); pModel; pModel = pModel->NextSiblingElement()) {
            const char* re = pModel->Attribute("red");
            const char* gre = pModel->Attribute("green");
            const char* bl = pModel->Attribute("blue");
            float red = re ? atof(re) : 255.0f;
            float green = gre ? atof(gre) : 255.0f;
            float blue = bl ? atof(bl) : 255.0f;
            g.addFile(pModel->Attribute("file"), red, green, blue);
        }
    }

    XMLElement* pGroupChild;
    for (pGroupChild = group->FirstChildElement("group"); pGroupChild; pGroupChild = pGroupChild->NextSiblingElement("group")) {
        Group groupR = parseGroup(pGroupChild);
        g.addGroup(groupR);
    }

    return g;
}

shared_ptr<Camera> XMLParser::parseCamera(XMLElement* camera) {
    shared_ptr<Camera> c = make_shared<Camera>();
    XMLElement* position = camera->FirstChildElement("position");
    XMLElement* lookAt = camera->FirstChildElement("lookAt");
    XMLElement* up = camera->FirstChildElement("up");
    XMLElement* projection = camera->FirstChildElement("projection");
    float x, y, z, fov, near, far;
    if (position) {
        position->QueryFloatAttribute("x", &x);
        position->QueryFloatAttribute("y", &y);
        position->QueryFloatAttribute("z", &z);
        c->addPosition(x, y, z);
    }
    if (lookAt) {
        lookAt->QueryFloatAttribute("x", &x);
        lookAt->QueryFloatAttribute("y", &y);
        lookAt->QueryFloatAttribute("z", &z);
        c->addLookAt(x, y, z);
    }
    if (up) {
        up->QueryFloatAttribute("x", &x);
        up->QueryFloatAttribute("y", &y);
        up->QueryFloatAttribute("z", &z);
        c->addUp(x, y, z);
    }
    if (projection) {
        projection->QueryFloatAttribute("fov", &fov);
        projection->QueryFloatAttribute("near", &near);
        projection->QueryFloatAttribute("far", &far);
        c->addProjection(fov, near, far);
    }

    return c;
}


vector<Group> XMLParser::parse() {
    XMLDocument xmlDoc;
    int err = xmlDoc.LoadFile(config_file.c_str());
    if(!err){
        cout << "Success on loading config file!" << endl;
        XMLElement* pWorld = xmlDoc.RootElement();

        if (!pWorld) {
            cout << "Error: could not find <world> element" << endl;
            exit(0);
        }

        XMLElement* pWindow = pWorld->FirstChildElement("window");
        if (pWindow) {
            if (pWindow->QueryIntAttribute("width", &window_width) != tinyxml2::XML_SUCCESS ||
                pWindow->QueryIntAttribute("height", &window_height) != tinyxml2::XML_SUCCESS)
            {
                cout << "Error: could not read <window> attributes" << endl;
                exit(0);
            }
        }
        else
        {
            cout << "Error: could not find <window> element, assuming default values!" << endl;
            window_width = 512, window_height = 512;
        }

        tinyxml2::XMLElement* pCamera = pWorld->FirstChildElement("camera");
        
        shared_ptr<Camera> cam = make_shared<Camera>();
        if (pCamera)
        {
            cam = parseCamera(pCamera);
        }
        else
        {
            cout << "Error: could not find <camera> element, assuming default values!" << endl;
            cam->addPosition(10.0f, 10.0f, 10.0f);
            cam->addLookAt(0.0f,0.0f,0.0f);
            cam->addUp(0.0f, 1.0f, 0.0f);
            cam->addProjection(60.0f, 1.0f, 1000.0f);
        }
        camera = cam;

        XMLElement* group;
        for (group = pWorld->FirstChildElement("group");group != NULL;group = group->NextSiblingElement("group")) {
            Group g = parseGroup(group);
            groups.push_back(g);
        }
    }
    else {
        xmlDoc.PrintError();
    }
    return groups;
}

unordered_set<string> XMLParser::getModels() {
    unordered_set<string> res;
    for (auto& g : groups) {
        unordered_set<string> models = g.getModels();
        for (auto& file : models) res.insert(file);
    }
    return res;
}

unordered_map<string, Point3D> XMLParser::getCamera() {
    unordered_map<string, Point3D> cam;
    cam["position"] = camera->camera_position;
    cam["lookAt"] =  camera->camera_lookAt;
    cam["up"] =  camera->camera_up;
    cam["projection"] =  camera->camera_projection;
    return cam;
}
