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
        >
            <div></div>
            {{error}}
        </div>
    </span>`,
    bindings: {},
    controller: [
        "$http",
        function ($http) {
            const apiUrl = `${settings.korp_backend_url}/lexicon?positional_attribute=error_type`

            const errors = new Set()

            $http.get(apiUrl).then((response) => {
                const resp = response.data.Arguments
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
        },
    ],
})
