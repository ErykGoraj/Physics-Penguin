#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:
    virtual ~Scene() = default;
    virtual void init() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
};

#endif // SCENE_H
