function startScript()
  local dialogo = GameObject.Instantiate("dialogo")
  local component = ComponentDialog.Instantiate()

  component:Say("Onde estou... O que esta acontecendo?")
  
  component:SetPlayerImage(path .. "resources\\hero\\hero.png")
  component:SetNpcImage(path .. "resources\\hero\\hero.png")
  component:SetFont(path .. "resources\\font\\fontlucida.png")

  component:AddTo(dialogo)
end