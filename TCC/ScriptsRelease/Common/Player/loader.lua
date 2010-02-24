function startScript()
  local player = GameObject.InstPersistent("player")
  --player:SetPosition(0,0,50)
  
  local component = ComponentSkeleton.Instantiate(path .. "resources\\level1\\models\\skeleton\\player.x", 8 )
  --This method is wrong. Bad code! The position should be in the game object
  component:SetPosition(0,0,50)
  component:AddTo(player)
 end