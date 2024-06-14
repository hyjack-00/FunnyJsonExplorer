#ifndef DRAWER_FACTORY_H
#define DRAWER_FACTORY_H

#include <memory>
#include <map>

#include "Drawer.h"
#include "Symbol.h"

#include "utils.h"

enum FactoryType {
    DefaultIcon,
    PokerIcon,
    ConfigIcon
};

// 建造者模式
class DrawerFactory {
protected:
    std::unique_ptr<Drawer> drawer;

    std::string branch      = "  ";
    std::string vertical    = "  ";
    std::string branchEnd   = "  ";
    std::string verticalEnd = "  ";
    std::string linkIcon      = " ";
    int linkLen = 2;

    std::string leafIcon      = " ";
    std::string containerIcon = " ";
    int iconLen = 1;

    // friend class Drawer;
    // void setLink(
    //     const std::string &branch, const std::string &vertical, 
    //     const std::string &branchEnd, const std::string &verticalEnd);
    void setIcon(
        const std::string &leafIcon, 
        const std::string &containerIcon);
    void setCharLen(
        const int linkLen, 
        const int iconLen);

    void build() {
        drawer->link.setLink(
            branch, vertical, branchEnd, verticalEnd, linkIcon, linkLen, iconLen);
        setIcon(leafIcon, containerIcon);
        setCharLen(linkLen, iconLen);
    }

public:
    DrawerFactory() = default;
    virtual ~DrawerFactory() = default;
    virtual void resetDefaultDrawer();
    virtual void resetTreeDrawer();
    virtual void resetRectDrawer();
    virtual std::unique_ptr<Drawer> createDefaultDrawer();
    virtual std::unique_ptr<Drawer> createTreeDrawer();
    virtual std::unique_ptr<Drawer> createRectDrawer();
    std::unique_ptr<Drawer> createDrawer(DrawerType drawerType);
    std::unique_ptr<Drawer> createDrawer(const std::string& drawerTypeName);
};

class DefaultDrawerFactory : public DrawerFactory {

};

class PokerDrawerFactory : public DrawerFactory {
private:

public:
    PokerDrawerFactory() {
        linkIcon = " ";
        leafIcon = "♤";
        containerIcon = "♢";
    }
    // std::unique_ptr<Drawer> createTreeDrawer() override;
    // std::unique_ptr<Drawer> createRectDrawer() override;
};

class ConfigDrawerFactory : public DrawerFactory {
private:
    std::string configFilePath;

public:
    ConfigDrawerFactory() = default;
    ConfigDrawerFactory(const std::string& configFilePath);
    // std::unique_ptr<Drawer> createTreeDrawer() override;
    // std::unique_ptr<Drawer> createRectDrawer() override;

    void loadConfigFile(const std::string& configFilePath);
};


class DrawerFactoryRegistry {
private:
    // FactoryName -> FactoryType
    std::map<std::string, FactoryType> factoryNameMap;
    // FactoryType -> DrawerFactory
    std::map<FactoryType, std::shared_ptr<DrawerFactory>> factoryMap;

public:
    DrawerFactoryRegistry() {
        registerFactory<DefaultDrawerFactory>(FactoryType::DefaultIcon, "default");
        registerFactory<PokerDrawerFactory>(FactoryType::PokerIcon, "poker");
        registerFactory<ConfigDrawerFactory>(FactoryType::ConfigIcon, "config");
    }

    template<typename ConcreteFactory> 
    void registerFactory(FactoryType factoryType, const std::string& factoryName) {
        factoryNameMap[factoryName] = factoryType;
        factoryMap[factoryType] = std::make_shared<ConcreteFactory>();
    }
    std::shared_ptr<DrawerFactory> getFactory(FactoryType factoryType);
    std::shared_ptr<DrawerFactory> getFactory(const std::string& factoryName);
};

#endif // DRAWER_FACTORY_H
