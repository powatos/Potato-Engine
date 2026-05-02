#pragma once

class Tickable 
{
public:

    bool isTicking() const;
    void SetTicking(bool isEnabled);

protected:
    Tickable() = default; // protected constructor lets ONLY derived classes call it
    virtual ~Tickable() = 0; // protected destructor stops compiler from allocating new, pure virtual makes abstract

    virtual void Tick(float dt);

private:
    bool bTicking;

};