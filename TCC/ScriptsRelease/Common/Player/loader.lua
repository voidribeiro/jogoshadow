function startScript()
  local player = GameObject.InstPersistent("player")
  player:SetPosition(50,30,50)

  local component = ComponentSkeleton.Instantiate(path .. "resources\\level1\\models\\skeleton\\player.x", 8 )
  component:AddTo(player)
 end