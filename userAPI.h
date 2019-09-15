#ifndef VEROFICATION_USERAPI_H
#define VEROFICATION_USERAPI_H

#include <cstdint>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <stdexcept>

/*!
 * \brief Данный класс реализует интерфейс для верификации прав пользователей на запрашиваемую функцию системы.
 * \author Фотиева Маргарита
 * \version 1.0
 * \date 07.07.2019
 */

class userAPI {
private:
    /// Структура, описывающая право
    struct law{
        int id; ///< Числовой индификатор права
        std::string name; ///< Название права
        std::string specification; ///< Описание права
    };
    /// Струтура, описывающая роль
    struct role{
        int id; ///< Числовой индификатор роли
        std::string name; ///< Название роли
        std::string specification; ///< Описание роли
        std::map<int, law> mapLaws; ///< Контейнер для хранения прав, доступных роле
    };
    /// Структура, описывающая пользователя
    struct user{
        int id; ///< Числовой индификатор пользователя
        std::map<int,role> mapRoles; ///< Контейнер для хранения ролей, принадлежащих пользователю
    };

    static std::map<int, user> users; ///< Контейнер для хренения всех пользователей
    static std::map<int, role> roles; ///< Контейнер для хренения всех пользователей
    static std::map<int, law> laws; ///< Контейнер для хренения всех пользователей
    static int generatorIdForUsers; ///< Переменная для генерации индификаторов пользователей
    static int generatorIdForRoles; ///< Переменная для генерации индификаторов ролей
    static int generatorIdForLaws; ///< Переменная для генерации индификаторов прав

public:
    /*!
     * Создает нового пользователя
     * \return созданный экземпляр струткуры user
     */
    static user addUser ();

    /*!
     * Создает новую роль
     * \param name название роли
     * \param specification описание роли
     * \return созданный экземпляр струткуры role
     */
    static role addRole (std::string name, std::string specification);

    /*!
    * Создает новое право
    * \param name название права
    * \param specification описание права
    * \return созданный экземпляр струткуры law
    */
    static law addLaw (std::string name, std::string specification);

    /*!
     * Удаляет роль из списка всех ролей по индификатору роли
     * @param roleId индификатор удаляемой роли
     */
    static void deleteRoleById (int roleId);

    /*!
     * Удаляет роль из списка всех ролей по названию роли
     * @param roleName название удаляемой роли
     */
    static void deleteRoleByName (std::string roleName);

    /*!
     * Удаляет право из списка всех прав по индификатору права
     * @param lawId индификатор права
     */
    static void deleteLawById (int lawId);

    /*!
     * Удаляет право из списка всех прав по названию права
     * @param lawName название права
     */
    static void deleteLawByName (std::string lawName);

    /*!
     * Возвращает значение user по индификатору пользователя
     * @param userId индификатор пользователя
     * @return пользователь, которому принадлежит переданный индификатор
     */
    static user getUserById (int userId);

    /*!
     * Возвращает значение role по индификатору роли
     * @param roleId индификатор роли
     * @return роль, которой принадлежит переданный индификатор
     */
    static role getRoleById (int roleId);

    /*!
     * Возвращает значение role по названию роли
     * @param roleName название роли
     * @return роль, которой принадлежит переданное название роли
     */
    static role getRoleByName (std::string roleName);

    /*!
     * Возвращает значение law по индификатору права
     * @param lawId индификатор права
     * @return право, которому принадлежит переданный индификатор
     */
    static law getLawById (int lawId);

    /*!
     * Возвращает значение law по названию права
     * @param lawName название права
     * @return право, которому принадлежит переданное название права
     */
    static law getLawByName (std::string lawName);

    /*!
     * Возвращает индификатор роли по названию роли
     * @param roleName название роли
     * @return индификатор роли
     */
    static int getRolesIdByName(std::string roleName);

    /*!
     * Возвращает индификатор права по названию права
     * @param lawName название права
     * @return индификатор права
     */
    static int getLawsIdByName(std::string lawName);

    /*!
     * Возвращает список пользовательских индификаторов
     * @return вектор, содержащий все пользовательские индификаторы
     */
    static std::vector<int> getlistUsersId ();

    /*!
     * Возвращает список индификаторов всех ролей
     * @return вектор, содержащий все индификаторы ролей
     */
    static std::vector<int> getlistRolesId ();

    /*!
     * Возвращает список индификаторов всех прав
     * @return вектор, содержащий все индификаторы прав
     */
    static std::vector<int> getlistlawsId ();

    /*!
     * Возвращает список названий всех ролей
     * @return вектор, содержащий все названия ролей
     */
    static std::vector<std::string> getlistRolesNames ();

    /*!
     * Возвращает список названий всех прав
     * @return вектор, содержащий все названия ролей
     */
    static std::vector<std::string> getlistLawsNames ();

    /*!
     * Назначает список ролей пользователю по индификаторам ролей
     * @param userId индификатор пользователя
     * @param listRolesIdes вектор, содержащий индификаторы ролей, кототрые необходимо назначить пользователю
     */
    static void appointListRolesForUserById (int userId, std::vector<int> listRolesIdes);

    /*!
     * Назначает список ролей пользователю по индификатору роли по названиям ролей
     * @param userId
     * @param listRolesNames
     */
    static void appointListRolesForUserByName (int userId, std::vector<std::string> listRolesNames);

    /*!
     * Добавляет роль пользователю по индификатору роли
     * @param userId индификатор пользователя
     * @param roleId индификатор роли
     */
    static void addRoleForUserById (int userId, int roleId);

    /*!
     * Добавляет роль пользователю по названию роли
     * @param userId индификатор пользователя
     * @param roleName название роли
     */
    static void addRoleForUserByName (int userId, std::string roleName);

    /*!
     * Удаляет роль у пользователя по индификатору роли
     * @param userId индификатор пользователя
     * @param roleId индификатор роли
     */
    static void deleteUsersRoleById (int userId, int roleId);

    /*!
     * Удаляет роль у пользователя по названию роли
     * @param userId индификатор пользователя
     * @param roleName название роли
     */
    static void deleteUsersRoleByName (int userId, std::string roleName);

    /*!
     * Назначает список прав роле по индификаторам прав
     * @param roleId индификатор роли
     * @param listLawsIdes вектор, содержащий индификаторы прав, котрые необходимо присовить роле
     */
    static void appointListLawsForRoleById (int roleId, std::vector<int> listLawsIdes);

    /*!
     * Назначает список прав роле по названиям прав
     * @param roleId индификатор роли
     * @param listLawsNames вектор, содержащий названия прав, котрые необходимо присовить роле
     */
    static void appointListLawsForRoleByName (int roleId, std::vector<std::string> listLawsNames);

    /*!
     * Добавляет право к роле по индификатору права
     * @param roleId индификатор роли
     * @param lawId индификатор права
     */
    static void addLawForRoleById (int roleId, int lawId);

    /*!
     * Добавляет право к роле по названию права
     * @param roleId индификатор роли
     * @param lawName название права
     */
    static void addLawForRoleByName (int roleId, std::string lawName);

    /*!
     * Удаляет право у роли по индификатору права
     * @param roleId индификатор роли
     * @param lawId индификатор права
     */
    static void deleteRolesLawById (int roleId, int lawId);

    /*!
     * Удаляет право у роли по названию права
     * @param roleId индификатор роли
     * @param lawName название права
     */
    static void deleteRolesLawByName (int roleId, std::string lawName);

    /*!
     * Изменяет название роли
     * @param roleId индификатор роли
     * @param newName новое название роли
     */
    static void changeRolesName (int roleId, std::string newName);

    /*!
     * Изменяет описание роли
     * @param roleId индификатор роли
     * @param newSpecification новое описание роли
     */
    static void changeRolesSpecification (int roleId, std::string newSpecification);

    /*!
     * Изменяет навзание права
     * @param lawId индификатор права
     * @param newName новое название права
     */
    static void changeLawsName (int lawId, std::string newName);

    /*!
     * Изменяет описание права
     * @param lawId индификатор права
     * @param newSpicification новое описание права
     */
    static void changeLawsSpecification (int lawId, std::string newSpicification);

    /*!
     * Возвращает список названий прав, принадлежащих роле
     * @param roleId индификатор роли
     * @return вектор, который содержит названия прав, принадлежащих роле
     */
    static std::vector<std::string> getListNamesOfRoleLaws (int roleId);

    /*!
     * Возвращает список индификаторов прав, принадлежащих роле
     * @param roleId индификатор роли
     * @return вектор, который содержит индификаторы прав, принадлежащих роле
     */
    static std::vector<int> getListIdOfRoleLaws (int roleId);

    /*!
     * Проверяет наличие права у пользователя
     * @param userId индификатор пользователя
     * @param lawId индификатор права
     * @return true, если право принадлежит пользователю, false - иначе
     */
    static bool thisLawsIsBelongToUser (int userId, int lawId);

    /*!
     * Выводит информвция про пользователя
     * @param userId индифиатор пользователя
     */
    static void printInformationAboutUser(int userId);
};


#endif //VEROFICATION_USERAPI_H
