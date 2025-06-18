

<script>
export default {
  name: 'GFormCreator',
  props: {
    conf: {
      type: Object,
      require: true
    },
    nonCheck: {
      type: Boolean,
      default: () => false
    }
  },
  data() {
    return {
      form: {}
    }
  },
  created() {
    const { items, cards, rules } = this.conf
    const { nonCheck } = this
    if (nonCheck && !rules) throw new Error('请传入rules')
    this.rulesHandler(rules)
    if (items) {
      this.reactiveFields(items)
    } else if (cards) {
      cards.forEach(card => {
        if (card.children) {
          this.reactiveFields(card.children)
        }
      })
    }

  },
  methods: {
    reactiveFields(items) {
      items.forEach(rowArr => {
        rowArr.forEach(item => {
          this.$set(this.form, item.key, item.value)
        })
      })
    },
    rulesHandler(rules) {
      for(let key in rules) {
        let valArr = rules[key]
        valArr.forEach(item => {
          if (item.validator) {
            item.validator = item.validator.bind(this)
          }
        })
      }
    },
    deepClone(data) {
      return JSON.parse(JSON.stringify(data))
    },
    doSubmit() {
      let { submit } = this.$listeners
      this.validate(submit)
      // submit('数据')
      // this.$emit('submit', this.deepClone(this.form))
    },
    validate(fn) {
      this.$refs.form.validate((valid) => {
        if (valid) {
          fn(this.getData())
        } else {
          fn(false)
        }
      })
    },
    getData() {
      return this.deepClone(this.form)
    },
    reset() {
      this.$refs.form.resetFields()
    },
    renderItem(item) {
      switch (item.type) {
        case 'input':
        case 'password':
        case 'textarea':
          return <el-input attrs={item.attrs} type={item.type} v-model={this.form[item.key]}></el-input>
        case 'radio':
          return item.options.map((opt, i) => {
              return <el-radio attrs={item.attrs} key={i} v-model={this.form[item.key]} label={opt.label}>{opt.text}</el-radio>
            })
        case 'select':
          return <el-select v-model={this.form[item.key]} attrs={item.attrs}>
            {item.options.map(opt => {
              return <el-option key={opt.key} label={opt.label} value={opt.value}></el-option>
            })}
          </el-select>
        case 'datetime':
          return <el-date-picker v-model={this.form[item.key]} type="date" placeholder="选择日期"></el-date-picker>
      }
    },
    renderColumns(columns) {
      return columns.map(item => {
        return <el-col xl={item.colspan} lg={item.colspan} md={12} sm={24} xs={24}>
          <el-form-item label={item.label} prop={item.key}>
            {this.renderItem(item)}
          </el-form-item>
        </el-col>
      })
    },
    renderRows(rows) {
      return rows.map(rowArr => {
        return <el-row>{this.renderColumns(rowArr)}</el-row>
      })
    },
    renderCards(cards) {
      return cards.map(card => {
        return (
            <el-card class="box-card">
              <div slot="header">
                <span>{card.name}</span>
              </div>
              { card.children && this.renderRows(card.children)}
            </el-card>
        )
      })
    }
  },
  render(h) {
    const { title, items, rules, cards } = this.conf
    const { form } = this
    return (
        <div class="form-box">
          <h1>{title}</h1>
          {title && <hr/>}
          <el-form ref="form" attrs={{model: form}} rules={rules} label-width="80px">
            { cards ? this.renderCards(cards) : this.renderRows(items)}
          </el-form>
          <div class="btns clear-fix">
            {this.$slots.default ? this.$slots.default : (
                <div>
                  <el-button type="primary" onClick={e => this.doSubmit()}>提交</el-button>
                  <el-button onClick={e => this.reset()}>重置</el-button>
                </div>
            )}
            { /* this.$scopedSlots.default(data) */ }
          </div>
        </div>
    )
  }
}
</script>

<style lang="scss" scoped>
.btns {
  text-align: center;
}
.box-card {
  margin-bottom: 10px;
  >div {
    >div {
      text-align: left;
    }
  }
}
.el-select, .el-input {
  width: 100%;
}
</style>