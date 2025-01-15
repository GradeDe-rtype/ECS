gravity = 9.8
speed_y = 0

function Update(entity)
    local speed = 100
    speed_y = speed_y + gravity * deltaTime
    move(entity, speed, speed_y)
    local x, y = getPosition(entity)
    if x >= 1400 or y >= 1000 then
        place(entity, -200, -200)
        speed_y = 0
        gravity = gravity + 10
    end
end

function onCollision(entity1, entity2) 
    print("coucou")
    place(entity1, -200, -200)
end
