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

class ExplosionConfig
{
private:
    float x;
    float y;
    std::string couleur;
    int nombre;
    float spread;
    float dureeDeVie;

public:
    ExplosionConfig(float x, float y, std::string couleur, int nombre, float spread, float dureeDeVie)
    {
        this->x = x;
        this->y = y;
        this->couleur = couleur;
        this->nombre = nombre = nombre;
        this->spread = spread;
        this->dureeDeVie = dureeDeVie;
    }

    float recupereX() 
    { 
        return x; 
    }
    float recupereY() 
    {
         return y; 
    }
    std::string recupereCouleur() 
    { 
        return couleur; 
    }
    int recupereNombre() 
    { return nombre; 
    }
    float recupereSpread() 
    { 
        return spread; 
    }
    float recupereDureeDeVie() 
    { 
        return dureeDeVie; 
    }

    void afficherConfig()
    {
        std::cout << "explosion dans localisation : "<< x <<", " << y <<" avec "<< nombre << "particules de couleur :"<<couleur<<".\n";
    }
};

class IParticlePrototype
{
public:
    virtual IParticlePrototype* clone() = 0;
    virtual void afficher() = 0;
    virtual ~IParticlePrototype() = default;
};

//prototype concret
class ParticlePrototype : public IParticlePrototype
{
private:
    float taille;
    std::string couleur;
    float vitesse;

public:
    ParticlePrototype(float taille, std::string couleur, float vitesse)
    {
        this->taille= taille;
        this->couleur = couleur;
        this->vitesse = vitesse;
    }

    ParticlePrototype(const ParticlePrototype& autre)
    {
        this->taille = autre.taille;
        this->couleur = autre.couleur;
        this->vitesse = autre.vitesse;
    }

    IParticlePrototype* clone() override
    {
        return new ParticlePrototype(*this);
    }

    void afficher() override
    {
        std::cout << "Particule avec taille: " <<taille<<" et couleur: " << couleur<< " et vitesse: "<<vitesse<<"\n";
    }
};

int main()
{
    FlyweightFactory* fwFactory = FlyweightFactory::recupereInstance();

    IParticleFlyweight* flyweight = fwFactory->creationFlyweight("flyweight1");
    flyweight->afficher();

    //exemple si le flyweight existe déjà
    IParticleFlyweight* fw2 = fwFactory->creationFlyweight("flyweight1");
    fw2->afficher();

    ExplosionConfig* config = new ExplosionConfig(10.0f, 20.0f, "rouge", 10, 20.0f, 5.0f);
    config->afficherConfig();

    std::cout << "creation du prototype : \n";
    IParticlePrototype* pp = new ParticlePrototype(2.5f, config->recupereCouleur(), 15.0f);
    pp->afficher();

    std::cout << "test clone prototype pour l'explosion : \n";
    IParticlePrototype* ppClone1 = pp->clone();
    IParticlePrototype* ppClone2 = pp->clone();
    ppClone1->afficher();
    ppClone2->afficher();

    delete fwFactory;
    delete config;
    delete pp;
    delete ppClone1;
    delete ppClone2;

    return 0;
}