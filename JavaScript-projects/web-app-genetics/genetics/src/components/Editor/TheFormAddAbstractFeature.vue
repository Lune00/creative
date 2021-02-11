<template lang="">
  <div>
    <h1>Ajouter une feature abstraite</h1>
    <form
      id="add_abstract_feature"
      @submit.prevent="checkForm"
      action="#"
      method="post"
    >
      <h2>Général</h2>

      <p>
        <label for="af_label">Libellé: </label>
        <input type="text" id="af_label" name="af_label" required />
      </p>

      <p>
        <label for="af_nature">Nature: </label>
        <select v-model="nature" name="af_nature" id="af_nature">
          <option :value="this.discreteNature()">Discrète</option>
          <option :value="this.continuousNature()">Continue</option>
        </select>
      </p>

      <p>
        <label for="nb_genes">Nombre de gènes: </label>
        <input type="number" id="af_nbgenes" name="nb_genes" min="1" />
      </p>

      <h2>Allèles</h2>
      <AllelesEditableList
        :nature="nature"
        :alleles="alleles"
        @add_allele="onAddAllele"
        @remove_allele="onRemoveAllele"
      ></AllelesEditableList>

      <h2>Règles de codominance</h2>
      <CodominanceRulesTable
        :alleles="alleles"
        :rules="rules"
      ></CodominanceRulesTable>

      <p>
        <input type="submit" value="Enregistrer" />
      </p>
    </form>
  </div>
</template>

<script>
import AllelesEditableList from '@/components/Editor/AllelesEditableList.vue'
import CodominanceRulesTable from '@/components/Editor/CodominanceRulesTable.vue'
import model from '@/models/model-helpers.js'
import Allele from '@/models/Allele.js'

export default {
  name: 'TheFormAddAbstractFeature',
  components: {
    AllelesEditableList,
    CodominanceRulesTable
  },
  data() {
    return {
      nature: '',
      alleles: [],
      rules: [],
      allele_id: 0
    }
  },
  methods: {
    checkForm: function(e) {
      console.log('check form', e)
      //Check que les alleles n'ont pas le meme key(label, unique pour l'user)
      //Check la completness des rules (lazy: calcule le nombre, si ça passe pas erreur, si ça passe vrai test)
    },
    discreteNature() {
      return model.discreteNature()
    },
    continuousNature() {
      return model.continuousNature()
    },
    onAddAllele() {
      const id = this.generateUniqueAlleleId()
      const allele = new Allele(id, id)
      this.alleles.push(allele)
      this.rules = model.rules_add_allele(this.rules, this.alleles, allele)
    },
    onRemoveAllele(index) {
      const removedAllele = this.alleles.splice(index, 1)
      this.rules = model.rules_remove_allele(this.rules, removedAllele)
    },
    generateUniqueAlleleId() {
      const id = this.allele_id
      this.allele_id++
      return id
    }
  }
}
</script>
<style lang="scss"></style>
