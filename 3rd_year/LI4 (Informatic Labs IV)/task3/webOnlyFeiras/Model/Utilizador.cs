using System.ComponentModel.DataAnnotations;
using Microsoft.AspNetCore.Identity;

namespace webOnlyFeiras.Model
{
    public class Utilizador : IdentityUser
    {        
        [Required]
        public string Nome { get; set; }

        [Required]
        public DateTime DataNascimento { get; set; }

        public string Morada { get; set; } = String.Empty;

        public int Contacto { get; set;}

        public int PathFotografiaPerfil { get; set; }
    }
}
