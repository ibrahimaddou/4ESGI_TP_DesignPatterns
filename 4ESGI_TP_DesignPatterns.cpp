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

public:
    FlyweightFactory()
    {
        std::cout << "initialisation.\n";
    }

    IParticleFlyweight* creationFlyweight(const std::string& flyParCle)
    {
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


int main()
{
    FlyweightFactory* fwFactory = new FlyweightFactory();

    IParticleFlyweight* flyweight = fwFactory->creationFlyweight("test de creation de flyweight");
    flyweight->afficher();

    delete fwFactory;

    return 0;
}