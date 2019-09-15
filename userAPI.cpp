#include "userAPI.h"

int userAPI::generatorIdForUsers = 0;
int userAPI::generatorIdForRoles = 0;
int userAPI::generatorIdForLaws = 0;
std::map<int, userAPI::user> userAPI::users;
std::map<int, userAPI::role> userAPI::roles;
std::map<int, userAPI::law> userAPI::laws;

userAPI::user userAPI::addUser() {
    user u;
    u.id = ++generatorIdForUsers;
    users[u.id] = u;
    return u;
}

userAPI::role userAPI::addRole(std::string name, std::string specification) {
    role r;
    r.id = ++generatorIdForRoles;
    r.name = name;
    r.specification = specification;
    roles[r.id] = r;
    return r;
}

userAPI::law userAPI::addLaw(std::string name, std::string specification) {
    law l;
    l.id = ++generatorIdForLaws;
    l.name = name;
    l.specification = specification;
    laws[l.id] = l;
    return l;
}

void userAPI::deleteRoleById(int roleId) {
    roles.erase(roleId);
    for (auto& u : users){
        u.second.mapRoles.erase(roleId);
    }
}

void userAPI::deleteRoleByName(std::string roleName) {
    int roleId = 0;
    for(auto& r : roles){
        if(r.second.name == roleName){
            roleId = r.first;
            userAPI::deleteRoleById(roleId);
            break;
        }
    }
}

void userAPI::deleteLawById(int lawId) {
    laws.erase(lawId);
    for(auto& r : roles){
        r.second.mapLaws.erase(lawId);
    }
    for(auto& u : users){
        for(auto& r : u.second.mapRoles){
            r.second.mapLaws.erase(lawId);
        }
    }
}

void userAPI::deleteLawByName(std::string lawName) {
    int lawId = 0;
    for(auto& l : laws){
        if(l.second.name == lawName){
            lawId = l.first;
            userAPI::deleteLawById(lawId);
            break;
        }
    }
}

userAPI::user userAPI::getUserById(int userId) {
    return users.find(userId)->second;
}

userAPI::role userAPI::getRoleById(int roleId) {
    if (roles.find(roleId) == roles.end()){
        throw std::runtime_error("Error! This role's id not found");
    }
    return roles.find(roleId)->second;
}

userAPI::role userAPI::getRoleByName(std::string roleName) {
    for(auto& r : roles){
        if(r.second.name == roleName){
            return r.second;
        }
    }
    throw std::runtime_error("Error! This role's name not found");
}

userAPI::law userAPI::getLawById(int lawId) {
    if (laws.find(lawId) == laws.end()){
        throw std::runtime_error("Error! This law's id not found");
    }
    return laws.find(lawId)->second;
}

userAPI::law userAPI::getLawByName(std::string lawName) {
    for(auto& l : laws){
        if(l.second.name == lawName){
            return l.second;
        }
    }
    throw std::runtime_error("Error! This law's name not found");
}

int userAPI::getRolesIdByName(std::string roleName) {
    for (auto& r : roles){
        if (r.second.name == roleName){
            return r.second.id;
        }
    }
    throw std::runtime_error("Error! This role's name not found");
}

int userAPI::getLawsIdByName(std::string lawName) {
    for (auto& l : laws){
        if (l.second.name == lawName){
            return l.second.id;
        }
    }
    throw std::runtime_error("Error! This law's name not found");
}

std::vector<int> userAPI::getlistUsersId() {
    std::vector<int>result;
    for(auto& u : users){
        result.push_back(u.first);
    }
    return result;
}

std::vector<int> userAPI::getlistRolesId() {
    std::vector<int>result;
    for(auto& r : roles){
        result.push_back(r.first);
    }
    return result;
}

std::vector<int> userAPI::getlistlawsId() {
    std::vector<int>result;
    for(auto& l : laws) {
        result.push_back(l.first);
    }
    return result;
}

std::vector<std::string> userAPI::getlistRolesNames() {
    std::vector<std::string>result;
    for(auto& r : roles){
        result.push_back(r.second.name);
    }
    return result;
}

std::vector<std::string> userAPI::getlistLawsNames() {
    std::vector<std::string>result;
    for(auto& l : laws){
        result.push_back(l.second.name);
    }
    return result;
}

void userAPI::appointListRolesForUserById(int userId, std::vector<int> listRolesIdes) {
    if (users.find(userId) != users.end()) {
        for (auto& it : listRolesIdes) {
            if(roles.find(it) != roles.end()) {
                users[userId].mapRoles[it] = userAPI::getRoleById(it);
            }
        }
    }
    else{
        throw std::runtime_error("Error, this users id does not exist");
    }
}

void userAPI::appointListRolesForUserByName(int userId, std::vector<std::string> listRolesNames) {
    if (users.find(userId) != users.end()) {
        for (auto& it : listRolesNames) {
            int roleId = userAPI::getRoleByName(it).id;
            if(roles.find(roleId) != roles.end()) {
                users[userId].mapRoles[roleId] = userAPI::getRoleById(roleId);
            }
        }
    }
    else{
        throw std::runtime_error("Error, this users id does not exist");
    }
}

void userAPI::addRoleForUserById(int userId, int roleId) {
    if (users.find(userId) != users.end()) {
        if (roles.find(roleId) != roles.end()) {
            users[userId].mapRoles[roleId] = userAPI::getRoleById(roleId);
        }
    }
    else {
        throw std::runtime_error("Error, this users id does not exist");
    }
}

void userAPI::addRoleForUserByName(int userId, std::string roleName) {
    if (users.find(userId) != users.end()) {
        int roleId = userAPI::getRoleByName(roleName).id;
        if (roles.find(roleId) != roles.end()) {
            users[userId].mapRoles[roleId] = userAPI::getRoleById(roleId);
        }
    } else {
        throw std::runtime_error("Error, this users id does not exist");
    }

}

void userAPI::deleteUsersRoleById(int userId, int roleId) {
    if (users.find(userId) != users.end()){
        if (roles.find(roleId) != roles.end()){
            users[userId].mapRoles.erase(roleId);
        }
    }
    else {
        throw std::runtime_error("Error, this users id does not exist");
    }
}

void userAPI::deleteUsersRoleByName(int userId, std::string roleName) {
    if (users.find(userId) != users.end()){
        int roleId = userAPI::getRoleByName(roleName).id;
        if (roles.find(roleId) != roles.end()){
            users[userId].mapRoles.erase(roleId);
        }
    }
    else {
        throw std::runtime_error("Error, this users id does not exist");
    }
}

void userAPI::appointListLawsForRoleById(int roleId, std::vector<int> listLawsIdes) {
    if (roles.find(roleId) != roles.end()) {
        for (auto& it : listLawsIdes) {
            if(laws.find(it) != laws.end()) {
                roles[roleId].mapLaws.insert(std::pair<int, law>(it, userAPI::getLawById(it)));
                for (auto& u : users){
                    if(u.second.mapRoles.find(roleId) != u.second.mapRoles.end()){
                        u.second.mapRoles[roleId] = roles[roleId];
                    }
                }
            }
        }
    }
    else{
        throw std::runtime_error("Error, this roles id does not exist");
    }
}

void userAPI::appointListLawsForRoleByName(int roleId, std::vector<std::string> listLawsNames) {
    if (roles.find(roleId) != roles.end()) {
        for (auto& it : listLawsNames) {
            int lawId = userAPI::getLawByName(it).id;
            if(laws.find(lawId) != laws.end()) {
                roles[roleId].mapLaws.insert(std::pair<int, law>(lawId, userAPI::getLawById(lawId)));
                for (auto& u : users){
                    if(u.second.mapRoles.find(roleId) != u.second.mapRoles.end()){
                        u.second.mapRoles[roleId] = roles[roleId];
                    }
                }
            }
        }
    }
    else{
        throw std::runtime_error("Error, this roles id does not exist");
    }

}

void userAPI::addLawForRoleById(int roleId, int lawId) {
    if (roles.find(roleId) != roles.end()) {
        if(laws.find(lawId) != laws.end()) {
            roles[roleId].mapLaws.insert(std::pair<int, law>(lawId, userAPI::getLawById(lawId)));
            for(auto& u : users){
                if (u.second.mapRoles.find(roleId) != u.second.mapRoles.end()){
                    u.second.mapRoles[roleId].mapLaws.insert(std::pair<int, law>(lawId, userAPI::getLawById(lawId)));
                }
            }
        }
    }
    else{
        throw std::runtime_error("Error, this roles id does not exist");
    }
}

void userAPI::addLawForRoleByName(int roleId, std::string lawName) {
    if (roles.find(roleId) != roles.end()) {
        int lawId = userAPI::getLawByName(lawName).id;
        if(laws.find(lawId) != laws.end()) {
            roles[roleId].mapLaws.insert(std::pair<int, law>(lawId, userAPI::getLawById(lawId)));
            for(auto& u : users){
                if (u.second.mapRoles.find(roleId) != u.second.mapRoles.end()){
                    u.second.mapRoles[roleId].mapLaws.insert(std::pair<int, law>(lawId, userAPI::getLawById(lawId)));
                }
            }
        }
    }
    else{
        throw std::runtime_error("Error, this roles id does not exist");
    }
}

void userAPI::deleteRolesLawById(int roleId, int lawId) {
    auto checkRole = roles.find(roleId);
    if (checkRole != roles.end()) {
        auto checkLaw = laws.find(lawId);
        if( checkLaw != laws.end()) {
            checkRole->second.mapLaws.erase(lawId);
            std::map<int, role>::iterator currentRole;
            for (auto& u : users){
                currentRole = u.second.mapRoles.find(roleId);
                if (currentRole != u.second.mapRoles.end()){
                    currentRole->second.mapLaws.erase(lawId);
                }
            }
        }
    }
    else{
        throw std::runtime_error("Error, this roles id does not exist");
    }
}

void userAPI::deleteRolesLawByName(int roleId, std::string lawName) {
    auto checkRole = roles.find(roleId);
    if (checkRole != roles.end()) {
        int lawId = userAPI::getLawByName(lawName).id;
        auto checkLaw = laws.find(lawId);
        if( checkLaw != laws.end()) {
            checkRole->second.mapLaws.erase(lawId);
            std::map<int, role>::iterator currentRole;
            for (auto& u : users){
                currentRole = u.second.mapRoles.find(roleId);
                if (currentRole != u.second.mapRoles.end()){
                    currentRole->second.mapLaws.erase(lawId);
                }
            }
        }
    }
    else{
        throw std::runtime_error("Error, this roles id does not exist");
    }
}

void userAPI::changeRolesName(int roleId, std::string newName) {
    if(roles.find(roleId) != roles.end()) {
        roles.find(roleId)->second.name = newName;
        std::map<int, role>::iterator currentRole;
        for (auto& u : users) {
            currentRole = u.second.mapRoles.find(roleId);
            if (currentRole != u.second.mapRoles.end()){
                currentRole->second.name = newName;
            }
        }
    }
    else{
        throw std::runtime_error("Error, this roles id does not exist");
    }
}

void userAPI::changeRolesSpecification(int roleId, std::string newSpecification) {
    if(roles.find(roleId) != roles.end()) {
        roles.find(roleId)->second.specification = newSpecification;
        std::map<int, role>::iterator currentRole;
        for (auto& u : users) {
            currentRole = u.second.mapRoles.find(roleId);
            if (currentRole != u.second.mapRoles.end()){
                currentRole->second.specification = newSpecification;
            }
        }
    }
    else{
        throw std::runtime_error("Error, this roles id does not exist");
    }
}

void userAPI::changeLawsName(int lawId, std::string newName) {
    if (laws.find(lawId) != laws.end()) {
        laws[lawId].name = newName;
        std::map<int,law>::iterator currentLaw;
        for (auto& r : roles) {
            currentLaw = r.second.mapLaws.find(lawId);
            if (currentLaw != r.second.mapLaws.end()){
                currentLaw->second.name = newName;
            }
        }
        for (auto& u : users) {
            for (auto& r : u.second.mapRoles) {
                currentLaw = r.second.mapLaws.find(lawId);
                if (currentLaw != r.second.mapLaws.end()){
                    currentLaw->second.name = newName;
                }
            }
        }
    }
    else{
        throw std::runtime_error("Error, this law's id does not exist");
    }
}

void userAPI::changeLawsSpecification(int lawId, std::string newSpicification) {
    if (laws.find(lawId) != laws.end()) {
        laws[lawId].specification = newSpicification;
        std::map<int,law>::iterator currentLaw;
        for (auto& r : roles) {
            currentLaw = r.second.mapLaws.find(lawId);
            if (currentLaw != r.second.mapLaws.end()){
                currentLaw->second.specification = newSpicification;
            }
        }
        for (auto& u : users) {
            for (auto& r : u.second.mapRoles) {
                currentLaw = r.second.mapLaws.find(lawId);
                if (currentLaw != r.second.mapLaws.end()){
                    currentLaw->second.specification = newSpicification;
                }
            }
        }
    }
    else{
        throw std::runtime_error("Error, this law's id does not exist");
    }
}

std::vector<std::string> userAPI::getListNamesOfRoleLaws(int roleId) {
    std::vector<std::string>result;
    auto neededRole = roles.find(roleId);
    if (neededRole != roles.end()) {
        for(auto& l : neededRole->second.mapLaws){
            result.push_back(l.second.name);
        }
    }
    else{
        throw std::runtime_error("Error, this role's name does not exist");
    }
    return result;
}

std::vector<int> userAPI::getListIdOfRoleLaws(int roleId) {
    std::vector<int>result;
    auto neededRole = roles.find(roleId);
    if (neededRole != roles.end()) {
        for(auto& l : neededRole->second.mapLaws){
            result.push_back(l.second.id);
        }
    }
    else{
        throw std::runtime_error("Error, this role's id does not exist");
    }
    return result;
}

bool userAPI::thisLawsIsBelongToUser(int userId, int lawId) {
    auto checkUser = users.find(userId);
    if(checkUser != users.end()){
        for(auto& r : checkUser->second.mapRoles){
            if (r.second.mapLaws.find(lawId) != r.second.mapLaws.end()){
                return true;
            }
        }
    }
    return false;
}

void userAPI::printInformationAboutUser(int userId) {
    auto neededUser = users.find(userId);
    if(neededUser == users.end()){
        throw std::runtime_error("Error, this user's id does not exist");
    }
    std::cout << "Информация о пользователе с id =  " << userId << std::endl;
    std::cout << "роли: ";
    for(auto& r : neededUser->second.mapRoles){
        std:: cout << r.second.name << " --> " << "права: ";
        for(auto& l : r.second.mapLaws){
            std::cout << std::endl << l.second.name ;
        }
        std::cout << std::endl;
    }

}






