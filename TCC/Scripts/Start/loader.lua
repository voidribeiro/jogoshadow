function startScript()
  print("Loading Start.")
  local gameObject = GameObject.Instantiate()
  local component = ComponentImage.Instantiate(path .. "resources\\splash\\lucasarts_logo.jpg")
  component:AddTo(gameObject)
end
