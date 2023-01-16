using System.ComponentModel.DataAnnotations;

namespace webOnlyFeiras.Model
{
    public class Carrinho
    {
        [Key]
        public int Id { get; set; }
        [Required]
        public Utilizador Utilizador { get; set; }
        public List<Produtos> Produtos { get; set; }
        public List<CodigoPromocional> CodigosPromocionais { get; set; }
    }

    
}
