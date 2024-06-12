#ifndef DRAWER_FACTORY_H
#define DRAWER_FACTORY_H

#include "Drawer.h"
#include <memory>

// 建造者模式
class DrawerFactory {
protected:
    std::unique_ptr<Drawer> drawer;

    // default 
    std::string branch      = "  ";
    std::string vertical    = "  ";
    std::string branchEnd   = "  ";
    std::string verticalEnd = "  ";
    std::string defaultIcon   = " ";
    std::string leafIcon      = " ";
    std::string containerIcon = " ";
    int linkLen = 2;
    int iconLen = 1;

    // friend class Drawer;
    void setLink(
        const std::string &branch, const std::string &vertical, 
        const std::string &branchEnd, const std::string &verticalEnd);
    void setIcon(
        const std::string &defaultIcon, 
        const std::string &leafIcon, 
        const std::string &ContainerIcon);
    void setCharLen(
        const int linkLen, 
        const int iconLen);
    void setAll() {
        setLink(branch, vertical, branchEnd, verticalEnd);
        setIcon(defaultIcon, leafIcon, containerIcon);
        setCharLen(linkLen, iconLen);
    }

public:
    virtual ~DrawerFactory() = default;
    virtual void resetTreeDrawer();
    virtual void resetRectDrawer();
    virtual std::unique_ptr<Drawer> createTreeDrawer();
    virtual std::unique_ptr<Drawer> createRectDrawer();
};

class PokerDrawerFactory : public DrawerFactory {
private:

public:
    PokerDrawerFactory() {
        defaultIcon = " ";
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
    ConfigDrawerFactory(const std::string& configFilePath);
    // std::unique_ptr<Drawer> createTreeDrawer() override;
    // std::unique_ptr<Drawer> createRectDrawer() override;
};

#endif // DRAWER_FACTORY_H
