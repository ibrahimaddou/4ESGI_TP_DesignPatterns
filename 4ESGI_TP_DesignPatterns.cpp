#include <iostream>
#include <string>
#include <vector>


class IParticleFlyweight
{
public:
    virtual void afficher() = 0;
    virtual ~IParticleFlyweight() = default;
};

//concret
class ParticleFlyweight : public IParticleFlyweight
{
private:
    std::string texture;
    std::string shader;
    std::string compPhysiques;

public:
    ParticleFlyweight(const std::string& type)
    {
        this->texture = "texture" + type + ".png";
        this->shader = "shade" + type + ".png";
        this->compPhysiques = "compPhysique" + type;
    }

    void afficher() override
    {
        std::cout << "donnees :  texture: " << texture << " et  Shader: " << shader << ")\n";
    }
};


class FlyweightFactory
{
private:
    std::vector<std::string> cles;
    std::vector<IParticleFlyweight*> flyweights;
    static FlyweightFactory* instance;
    FlyweightFactory()
    {
        std::cout << "initialisation.\n";
    }

public:
    
    static FlyweightFactory* recupereInstance()
    {
        if (instance == nullptr)
        {
            instance = new FlyweightFactory();
        }
        return instance;
    }

    IParticleFlyweight* creationFlyweight(const std::string& flyParCle)
    {
        //si le  flyweight existe déjà
        for (size_t i = 0; i < cles.size(); i++)
        {
            if (cles[i] == flyParCle)
            {
                std::cout << "reutilisation de flyweight : " << flyParCle << "\n";
                return flyweights[i];
            }
        }

        std::cout << "Creation de flyweight\n";
        IParticleFlyweight* nvFlyweight = new ParticleFlyweight(flyParCle);

        cles.push_back(flyParCle);
        flyweights.push_back(nvFlyweight);

        return nvFlyweight;
    }

    ~FlyweightFactory()
    {
        for (size_t i = 0; i < flyweights.size(); i++)
        {
            delete flyweights[i];
        }
    }
};

FlyweightFactory* FlyweightFactory::instance = nullptr;

int main()
{
    FlyweightFactory* fwFactory = FlyweightFactory::recupereInstance();

    IParticleFlyweight* flyweight = fwFactory->creationFlyweight("flyweight1");
    flyweight->afficher();

    //exemple si le flyweight existe déjà
    IParticleFlyweight* fw2 = fwFactory->creationFlyweight("flyweight1");
    fw2->afficher();

    delete fwFactory;

    return 0;
}