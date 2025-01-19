-- gravity = 9.8
-- speed_y = 0
speed = 100

function Update(entity)
    -- speed_y = speed_y + gravity * deltaTime
    move(entity, speed, 0)
    local x, y = getPosition(entity)
    if x >= 1400 or y >= 1000 then
        place(entity, -500, math.random(0, 1080))
        if speed > 150 then
            speed = speed - 150
        end
        -- speed_y = 0
        -- gravity = gravity + 10
    end
end

function onCollision(entity1, entity2) 
    place(entity2, -500, math.random(0, 1080))
    speed = speed + 75
end
