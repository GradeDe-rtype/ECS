gravity = 9.8
speed_y = 0

function Update(entity)
    local speed = 100
    speed_y = speed_y + gravity * deltaTime
    move(entity, speed, speed_y)
    local x, y = getPosition(entity)
    if x >= 1400 or y >= 1000 then
        place(entity, 0, 0)
        speed_y = 0
        gravity = gravity + 10
    end
end

function onCollision(entity1, entity2) 
    place(entity2, 0, 0)
end
