/** @format */
import angular, { element } from "angular"
import { html } from "@/util"
import { generateColors } from "@/colors"
import settings from "@/settings"

export default angular.module("korpApp").component("wordColorMeanings", {
    template: html`<span class="wordColors">
        <div
            ng-repeat="error in $ctrl.errors"
            ng-style="{'text-align': 'center', 'padding': '2px', 'border-radius': '6px', 'background-color': $ctrl.colors[$index]}"
            class="{{error}}_meaning"
        >
            <a href="" ng-click="$ctrl.selectItem(error)">
                <div></div>
                {{error}}
            </a>
        </div>
    </span>`,
    bindings: {
        changeColor: "&",
        corpus: "<",
    },
    controller: [
        "$http",
        function ($http) {
            let $ctrl = this
            let apiUrl = ""

            $ctrl.$onInit = () => {
                apiUrl = `${
                    settings.korp_backend_url
                }/lexicon?positional_attribute=error_type&corpus=${$ctrl.corpus.join(",")}`
                addColors(apiUrl)
            }

            $ctrl.$onChange = () => {
                addColors(apiUrl)
            }

            const addColors = (apiURL) => {
                const errors = new Set()
                $http.get(apiURL).then((response) => {
                    const resp = response.data.Arguments
                    if (resp === undefined) return
                    for (let index = 0; index < resp.length; index++) {
                        const error_type = resp[index]
                        if (error_type === "_" || error_type == "__UNDEF__" || error_type === "") continue
                        const parts = error_type.split("|")
                        for (let index = 0; index < parts.length; index++) {
                            const part = parts[index]
                            errors.add(part)
                        }
                    }
                    this.errors = Array.from(errors)

                    this.colors = [
                        ...generateColors("#FA9189", "#D1BDFF", Math.floor(errors.size / 2)),
                        ...generateColors("#7AD6EB", "#46E079", errors.size - Math.floor(errors.size / 2)),
                    ]
                })

                $ctrl.selected = "_"

                $ctrl.selectItem = function (error) {
                    //Change current selected color
                    if (error == $ctrl.selected) {
                        $ctrl.selected = "_"
                        error = "_"
                    } else {
                        $ctrl.selected = error
                    }
                    //console.log(error)

                    //Visual update
                    ;[...errors].forEach((errorType) => {
                        ;[...document.getElementsByClassName(errorType + "_meaning")].forEach((meaning) => {
                            let style = meaning.getAttribute("style")
                            if (error == errorType) {
                                style += " border-style: solid; border-width: 2px; border-color: black"
                                style = style.replace("padding: 2px", "padding: 0px")
                            } else {
                                style = style.replace(
                                    " border-style: solid; border-width: 2px; border-color: black",
                                    ""
                                )
                                style = style.replace("padding: 0px", "padding: 2px")
                            }
                            meaning.setAttribute("style", style)
                        })
                    })

                    //Update colors
                    $ctrl.changeColor({ error: error })
                }
            }
        },
    ],
})
