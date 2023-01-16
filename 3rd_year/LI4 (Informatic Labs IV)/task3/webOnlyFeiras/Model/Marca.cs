using System.ComponentModel.DataAnnotations;

namespace webOnlyFeiras.Model
{
    public class Marca
    {
        [Key]
        public string Nome { get; set; }
        [Required]
        public Utilizador Representante { get; set; }
        [Required]
        public DateTime DataFundacao { get; set; }
        public string Nacionalidade { get; set; } = String.Empty;
        public string Mercado { get; set; } = String.Empty;
        [Required]
        public string ImagePathLogotipo { get; set; } = String.Empty;
        [Required]
        public string Morada { get; set; } = String.Empty;
        [Required]
        public int NIPC { get; set; }
        public bool Verificada { get; set; }
    }
}
