function startScript()
  --criar um objeto
  local gameObject = GameObject.Instantiate()
  
  --Load Splash Image
  local component = ComponentModel.Instantiate(path .. "resources\\level1\\models\\faerie.md2")
  component:SetTexture(path .. "resources\\level1\\textures\\faerie2.bmp")
  component:AddTo(gameObject)                                              

end
