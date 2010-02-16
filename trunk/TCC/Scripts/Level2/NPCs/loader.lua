function startScript()
  print("Loading NPCs from Level2")

    --criar um objeto
  local gameObject = GameObject.Instantiate("skeleton")

  local component = ComponentSkeleton.Instantiate(path .. "resources\\level2\\models\\skeleton\\player.x", 8 )
  component:AddTo(gameObject)

end
