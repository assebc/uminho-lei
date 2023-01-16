using System.ComponentModel.DataAnnotations;

namespace webOnlyFeiras.Model
{
    public class Encomenda
    {
        public enum EstadoEncomenda
        {
            Pendente,
            Enviada
        }

        [Key]
        public int Id { get; set; }
        [Required]
        public List<Produto> Produtos { get; set; }
        public string MoradaEnvio { get; set; } = String.Empty;
        public DateTime DataEnvio { get; set; }
        public DateTime DataEncomenda { get; set; }
        public EstadoEncomenda Estado { get; set; }


    }
}
