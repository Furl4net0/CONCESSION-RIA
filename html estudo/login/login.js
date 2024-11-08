function validateForm() {
   
    const name = document.getElementById("name").value;
    const email = document.getElementById("email").value;
    const phone = document.getElementById("phone").value;

    
    if (name.length < 2) {
        alert("Por favor, insira um nome válido com pelo menos 2 caracteres.");
        return false;
    }

  
    const emailPattern = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    if (!emailPattern.test(email)) {
        alert("Por favor, insira um email válido.");
        return false;
    }

 
    const phonePattern = /^\d{10,11}$/;
    if (!phonePattern.test(phone)) {
        alert("Por favor, insira um número de telefone válido com 10 ou 11 dígitos.");
        return false;
    }

 
    alert("Formulário enviado com sucesso!");
    return true;
}
