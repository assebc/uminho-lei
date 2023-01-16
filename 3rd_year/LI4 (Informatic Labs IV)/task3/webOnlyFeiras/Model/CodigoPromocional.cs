using System.ComponentModel.DataAnnotations;

namespace webOnlyFeiras.Model
{
    public class CodigoPromocional
    {
        [Key]
        public string Codigo { get; set; }
        [Required]
        public int PromocaoAplicada { get; set; }
    }
}
